/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:38 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/21 08:50:18 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/*
 * The JOIN command is used by a user to join a channel, if the channel doesn't exist, it is created.
 * The channel name must start with a '#'
 * In case of `JOIN 0`, the user leaves all the channels he is in.
 */
void	Server::joinCommand(const strings& commands, int &cindex)
{
	if (commands.size() < 2)
	{
		std::cerr << "Error: not enough parameters" << std::endl;
		clients[cindex].sendMessage(ERR_NEEDMOREPARAMS, clients[cindex].getNickname() + " " + commands[0] + " :Not enough parameters");
		return;
	}
	// Handling in case user wants to leave all channels
	if (commands[1] == "0")
	{
		for (t_channelIterator it = channels.begin(); it != channels.end(); it++)
		{
			if (it->second->isMember(&clients[cindex]))
			{
				std::vector<std::string> partTokens;

				// Prepare PART command to leave the channel
				partTokens.push_back("PART");
				partTokens.push_back(it->second->getName());
				partCommand(partTokens, cindex);
			}
		}
		clients[cindex].setNbChannels(0);
		return;
	}
	// Split the provided channel names by comma (',')
	std::vector<std::string> channel_names = split(commands[1], ',');
	std::vector<Channel *> channels_to_sub;
	for (std::vector<std::string>::iterator it_names = channel_names.begin(); it_names != channel_names.end(); it_names++)
	{
		// Validate the channel name format
		if (*it_names == "#" || (*it_names)[0] != '#' || it_names->find(',') != std::string::npos || it_names->find(' ') != std::string::npos || it_names->find('\x07') != std::string::npos)
		{
			clients[cindex].sendMessage(ERR_BADCHANMASK,*it_names + " :Cannot join channel: Channel must start with # and cannot contain spaces, commas or \\x07");
			continue ;
		}
		// Check if the user has already joined too many channels, unsure how many we want to set this to (defaul 10)
		std::cout << "Number of channels: " << clients[cindex].getNbChannels() << std::endl;
		if (clients[cindex].getNbChannels() >= 10)
		{
			clients[cindex].sendMessage(ERR_TOOMANYCHANNELS, clients[cindex].getNickname() + " " + *(it_names) + " :You have joined too many channels");
			continue ;
		}
		// If the channel exists, add it to the list of channels to join
		if (existsChannel(*it_names))
		{
			channels_to_sub.push_back(this->getChannels()[*it_names]);
		}
		else
		{
			// If the channel does not exist, create a new one and add it to the map
			std::string s = "";
			Channel *channel_to_add = new Channel(s, *it_names, &clients[cindex]);
			channel_to_add->addClient(&clients[cindex]);
			channels_to_sub.push_back(channel_to_add);
			channels[*it_names] = channel_to_add;
		}
	}
	// ------------------------------------------------------------
	for (std::vector<Channel *>::iterator it = channels_to_sub.begin(); it != channels_to_sub.end(); it++)
	{
		// Check if the channel is invite-only and if the user is invited
		if ((*it)->getMode().find('i') != std::string::npos && (*it)->isInvited(&clients[cindex]))
		{
			clients[cindex].sendMessage(ERR_INVITEONLYCHAN, clients[cindex].getNickname() + " " + (*it)->getName() + " :Cannot join channel (+i)");
			continue ;
		}
		(*it)->addClient(&clients[cindex]);
		// If the user was previously invited, remove the invitation
		if ((*it)->isInvited(&clients[cindex]))
			(*it)->delInvited(&clients[cindex]);
		// Send JOIN message to all channel members
		(*it)->sendMessage(clients[cindex].getNickname(), "JOIN", (*it)->getName());
		// If the channel has a topic, send it to the user
		if ((*it)->getTopic() != "")
			clients[cindex].sendMessage(RPL_TOPIC, clients[cindex].getNickname() + " " + (*it)->getName() + " :" + (*it)->getTopic());
		// Increment the number of channels the user is part of
		clients[cindex].setNbChannels(clients[cindex].getNbChannels() + 1);
		// Send the list of users in the channel
		for (std::map<std::string, Client *>::const_iterator it_client = (*it)->getClients().begin(); it_client != (*it)->getClients().end(); it_client++)
		{
			clients[cindex].sendMessage(RPL_NAMREPLY, clients[cindex].getNickname() + " " + (*it)->getSymbol() + " " \
				+ (*it)->getName() + " :" + (*it)->getPrefix(it_client->second) + (*it_client).second->getNickname());
		}
		// Signal end of NAMES list
		clients[cindex].sendMessage(RPL_ENDOFNAMES, clients[cindex].getNickname() + " " + (*it)->getName() + " :End of /NAMES list");
	}
}

