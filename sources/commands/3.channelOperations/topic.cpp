/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:38 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/11/07 11:30:21 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/*
 * The TOPIC command is used to get or set the topic of a channel.
 */
void	Server::topicCommand(const strings& commands, int& cindex)
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
		clients[cindex].sendMessage(ERR_NEEDMOREPARAMS, clients[cindex].getNickname() + " " + commands[0] + " :Not enough parameters");
		return;
	}

	// Check if the channel exists
	if (!existsChannel(commands[1]))
	{
		clients[cindex].sendMessage(ERR_NOSUCHCHANNEL, clients[cindex].getNickname() + " " + commands[1] + " :No such channel");
		return;
	}

	Channel *channel = this->getChannels()[commands[1]];
	// Check if the user is a member of the channel
	if (!channel->isMember(&clients[cindex]))
	{
		clients[cindex].sendMessage(ERR_NOTONCHANNEL, clients[cindex].getNickname() + " " + commands[1] + " :You're not on that channel");
		return;
	}
	// If only the channel name is provided, return the current topic
	if (commands.size() == 2)
	{
		if (channel->getTopic().empty())
			clients[cindex].sendMessage(RPL_NOTOPIC, clients[cindex].getNickname() + " " + commands[1] + " :No topic is set");
		else
			clients[cindex].sendMessage(RPL_TOPIC, clients[cindex].getNickname() + " " + commands[1] + " :" + channel->getTopic());
	}
	// If a topic is provided, set the new topic
	else
	{
		// Check if the user has permission to set the topic
		if (channel->getMode().find('t') == std::string::npos || channel->isOperator(&clients[cindex]))
		{
			// Concatenate all parts of the topic starting from commands[2]
			std::string newTopic = commands[2];
			for (size_t i = 3; i < commands.size(); ++i)
				newTopic += " " + commands[i];

			channel->setTopic(newTopic);
			channel->sendMessage(clients[cindex].getNickname(), "TOPIC", commands[1] + " :" + newTopic);
		}
		else
		{
			clients[cindex].sendMessage(ERR_CHANOPRIVSNEEDED, clients[cindex].getNickname() + " " + commands[1] + " :You're not channel operator");
		}
	}
}
