/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:38 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/16 11:32:54 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"


/*
 * The PART command is used to leave a channel.
 * If the client is the last one in the channel, the channel is destroyed.
 */
void	Server::partCommand(const strings& commands, int& cindex)
{
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
		// if user is in the channel, send a message to all users in the channel and leave it
		channel->sendMessage(clients[cindex].getNickname(), "PART", *it + " " + commands[2]);
		channel->removeClient(&clients[cindex]);
		if (channel->isEmpty())
			removeChannel(*it); // if user is the last in the channel, delete it
	}
}
