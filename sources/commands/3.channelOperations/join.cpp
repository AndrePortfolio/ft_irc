/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:38 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/11/20 09:35:24 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/*
 * The JOIN command is used by a user to join a channel, if the channel doesn't exist, it is created.
 * The channel name must start with a '#'
 * In case of `JOIN 0`, the user leaves all the channels he is in.
 */
void Server::joinCommand(const strings& commands, int &cindex)
{
	bool	authenticated = clients[cindex].getStatus();

	if (authenticated != true)
	{
		std::string outputMsg = feedbackClient(ERR_NOTAUTHENTICATED);
		send(clients[cindex].getSocket(), outputMsg.c_str(), outputMsg.length(), DEFAULT);
		return ;
	}
	if (commands.size() < 2)
	{
		std::cerr << "Error: not enough parameters" << std::endl;
		clients[cindex].sendMessage(ERR_NEEDMOREPARAMS, clients[cindex].getNickname() + " " + commands[0] + " :Not enough parameters");
		return;
	}

	// Handling in case user wants to leave all channels
    if (commands[1] == "0")
	{
		handleLeaveAllChannels(commands, cindex);
		return ;
	}

	// Split the provided channel names by comma (',') and handle potential passwords
	std::vector<std::string> channel_names;
	std::vector<std::string> passwords;
	parseChannelNamesAndPasswords(commands[1], channel_names, passwords);

	std::vector<Channel *> channels_to_sub;

	// Process each channel name
	processChannelNames(channel_names, cindex);

	// Process each channel name along with its password
	for (size_t i = 0; i < channel_names.size(); ++i)
	{
		std::string channelName = channel_names[i];
		std::string channelPassword;
		if (i < passwords.size())
			channelPassword = passwords[i];
		else
			channelPassword = "";

		// Validate and process the channel with its respective password
		handleExistingOrNewChannel(channelName, channelPassword, cindex, channels_to_sub);
	}

	// Join the channels
	joinChannels(channels_to_sub, cindex);
}

void Server::deleteChannel(const std::string& channelName)
{
	// Ensure the channel exists before deleting
	if (existsChannel(channelName))
	{
		Channel* channel_to_delete = channels[channelName];
		delete channel_to_delete;
		channels.erase(channelName); // Remove channel from the map
	}
}

void Server::handleLeaveAllChannels(const strings& commands, int& cindex)
{
	(void) commands;
	std::vector<std::string> channelsToLeave;

	// Populate the list with channel names the user is currently a member of
	for (t_channelIterator it = channels.begin(); it != channels.end(); it++)
	{
		if (it->second->isMember(&clients[cindex]))
		{
			channelsToLeave.push_back(it->second->getName());
		}
	}

	// Iterate over the list and leave each channel
	for (std::vector<std::string>::iterator it = channelsToLeave.begin(); it != channelsToLeave.end(); ++it)
	{
		std::vector<std::string> partTokens;

		// Prepare PART command to leave the channel
		partTokens.push_back("PART");
		partTokens.push_back(*it);
		partCommand(partTokens, cindex);

		// If the channel is empty after the client leaves, delete it
		if (channels[*it]->getUserCount() == 0)
		{
			deleteChannel(*it);
		}
	}

	// Reset the number of channels the client is part of
	clients[cindex].setNbChannels(0);
}


void Server::parseChannelNamesAndPasswords(const std::string& input, std::vector<std::string>& channel_names, std::vector<std::string>& passwords)
{
	// Split by space to separate channels and passwords
	std::vector<std::string> splitInput = split(input, ' ');

	// Split channel names by comma
	channel_names = split(splitInput[0], ',');

	// Remove the : from the start of the first channel name
	if (!channel_names.empty() && channel_names[0][0] == ':')
		channel_names[0] = channel_names[0].substr(1);

	// If there are passwords provided, split them by comma
	if (splitInput.size() > 1)
		passwords = split(splitInput[1], ',');
}

void Server::processChannelNames(const std::vector<std::string>& channel_names, int &cindex)
{
	for (std::vector<std::string>::const_iterator it_names = channel_names.begin(); it_names != channel_names.end(); it_names++)
	{
		// Validate the channel name format
		if (!isValidChannelName(*it_names))
		{
			clients[cindex].sendMessage(ERR_BADCHANMASK, *it_names + " :Cannot join channel: Channel must start with # and cannot contain spaces, commas or \\x07");
			continue;
		}

		// Check if the user has already joined too many channels (default limit is 10)
		if (clients[cindex].getNbChannels() >= 10)
		{
			clients[cindex].sendMessage(ERR_TOOMANYCHANNELS, clients[cindex].getNickname() + " " + *(it_names) + " :You have joined too many channels");
			continue;
		}
	}
}

bool Server::isValidChannelName(const std::string& channelName)
{
	if (channelName == "#")
		return (false);
	if (channelName[0] != '#')
		return (false);
	if (channelName.find(',') != std::string::npos)
		return (false);
	if (channelName.find(' ') != std::string::npos)
		return (false);
	if (channelName.find('\x07') != std::string::npos)
		return (false);
	return (true);
}

void Server::handleExistingOrNewChannel(const std::string& channelName, const std::string& channelPassword, int &cindex, std::vector<Channel *> &channels_to_sub)
{
	if (existsChannel(channelName))
	{
		Channel* channel = this->getChannels()[channelName];

		// Check if the channel is in +k mode (requires a password)
		if (channel->getMode().find('k') != std::string::npos)
		{
			if (channelPassword.empty() || channelPassword != channel->getPassword())
			{
				clients[cindex].sendMessage(ERR_BADCHANNELKEY, clients[cindex].getNickname() + " " + channelName + " :Cannot join channel (Incorrect password)");
				return;
			}
		}

		// Check if the channel is in +l mode (user limit)
		if (channel->getMode().find('l') != std::string::npos && channel->getUserCount() >= channel->getUserLimit())
		{
			clients[cindex].sendMessage(ERR_CHANNELISFULL, clients[cindex].getNickname() + " " + channelName + " :Cannot join channel (Channel is full)");
			return;
		}

		channels_to_sub.push_back(channel);
	}
	else
	{
		// If the channel does not exist, create a new one and add it to the map
		createNewChannel(channelName, channelPassword, cindex, channels_to_sub);
		// Assign the user as the operator of the newly created channel
		channels_to_sub.back()->addOperator(&clients[cindex]);
		// Notify the user that they are the channel operator
		clients[cindex].sendMessage(RPL_YOUAREOPER, clients[cindex].getNickname() + " " + channelName + " :You are now the channel operator");
	}
}

void Server::createNewChannel(const std::string& channelName, const std::string& channelPassword, int& cindex, std::vector<Channel*>& channels_to_sub)
{
    // Allocate memory for a new channel
    Channel* channel_to_add = new Channel("" ,channelName, &clients[cindex]);

    // If a password is provided, set it
    if (!channelPassword.empty())
    {
        channel_to_add->setPassword(channelPassword);
        channel_to_add->addMode("k");
    }

    // Add the client to the new channel
    channel_to_add->addClient(&clients[cindex]);
    channels_to_sub.push_back(channel_to_add);
    channels[channelName] = channel_to_add;
}

void Server::joinChannels(std::vector<Channel *>& channels_to_sub, int &cindex)
{
	for (std::vector<Channel *>::iterator it = channels_to_sub.begin(); it != channels_to_sub.end(); it++)
	{
		// Check if the channel is invite-only and if the user is invited
		if ((*it)->getMode().find('i') != std::string::npos && !(*it)->isInvited(&clients[cindex]))
		{
			clients[cindex].sendMessage(ERR_INVITEONLYCHAN, clients[cindex].getNickname() + " " + (*it)->getName() + " :Cannot join channel (+i)");
			continue;
		}

		// Add client to channel
		(*it)->addClient(&clients[cindex]);

		// If the user was previously invited, remove the invitation
		if ((*it)->isInvited(&clients[cindex]))
			(*it)->delInvited(&clients[cindex]);

		// Send JOIN message to all channel members, including the one joining
		for (std::map<std::string, Client *>::const_iterator it_client = (*it)->getClients().begin(); it_client != (*it)->getClients().end(); it_client++)
		{
			it_client->second->sendMessage(clients[cindex].getNickname(), "JOIN", (*it)->getName());
		}

		// Send information about the topic of the channel
		if (!(*it)->getTopic().empty())
			clients[cindex].sendMessage(RPL_TOPIC, clients[cindex].getNickname() + " " + (*it)->getName() + " :" + (*it)->getTopic());

		// Increment the number of channels the user is part of
		clients[cindex].setNbChannels(clients[cindex].getNbChannels() + 1);

		// Update the user count for the channel
		(*it)->setUserCount((*it)->getUserCount() + 1);

		// Send the list of users in the channel (RPL_NAMREPLY)
		std::string usersList;
		for (std::map<std::string, Client *>::const_iterator it_client = (*it)->getClients().begin(); it_client != (*it)->getClients().end(); it_client++)
		{
			usersList += (*it)->getPrefix(it_client->second) + it_client->second->getNickname() + " ";
		}
		clients[cindex].sendMessage(RPL_NAMREPLY, clients[cindex].getNickname() + " " + (*it)->getSymbol() + " " + (*it)->getName() + " :" + usersList);

		// Signal end of NAMES list (RPL_ENDOFNAMES)
		clients[cindex].sendMessage(RPL_ENDOFNAMES, clients[cindex].getNickname() + " " + (*it)->getName() + " :End of /NAMES list");
	}
}
