/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:38 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/11/07 11:30:29 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"


/*
 * The PART command is used to leave a channel.
 * If the client is the last one in the channel, the channel is destroyed.
 */
void	Server::partCommand(const strings& commands, int& cindex)
{
	bool	authenticated = clients[cindex].getStatus();

	if (authenticated != true)
	{
		std::string outputMsg = feedbackClient(ERR_NOTAUTHENTICATED);
		send(clients[cindex].getSocket(), outputMsg.c_str(), outputMsg.length(), DEFAULT);
		return ;
	}
	// error handling
	if (commands.size() < 2)
	{
		clients[cindex].sendMessage(ERR_NEEDMOREPARAMS, clients[cindex].getNickname() + " " + commands[0] + " :Not enough parameters");
		return;
	}

	// handling for example: PART #channel1,#channel2 :Goodbye cruel world!
	std::vector<std::string> channel_names = split(commands[1], ',');
	for (std::vector<std::string>::iterator it = channel_names.begin(); it != channel_names.end(); it++)
	{
		if (!existsChannel(*it))
		{
			clients[cindex].sendMessage(ERR_NOSUCHCHANNEL, clients[cindex].getNickname() + " " + *it + " :No such channel");
			continue ;
		}
		Channel *channel = channels[*it];
		//after checking if channel exists, check if user is in the channel
		if (!channel->isMember(&clients[cindex]))
		{
			clients[cindex].sendMessage(ERR_NOTONCHANNEL, clients[cindex].getNickname() + " " + *it + " :You're not on that channel");
			continue ;
		}
		// checks if user has a parting message, if so, send it to the channel
		if (commands.size() > 2 && !commands[2].empty())
		{
			std::string fullMessage;
			std::string::size_type i = 2;
			while (i < commands.size())
			{
				fullMessage.append(commands[i]);
				++i;
				if (i < commands.size())
					fullMessage.append(" ");
			}
    		channel->sendMessage(clients[cindex].getNickname(), "PART", *it + " " + fullMessage);
		}
		else
			channel->sendMessage(clients[cindex].getNickname(), "PART", *it);

		// Remove client from channel and update user count
		channel->removeClient(&clients[cindex]);
		channel->setUserCount(channel->getUserCount() - 1);
		if (channel->isEmpty())
			removeChannel(*it); // if user is the last in the channel, delete it
	}
}
