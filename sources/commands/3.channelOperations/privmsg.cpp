/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:38 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/30 13:25:55 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/*
 * The PRIVMSG command is used to send private messages between users.
 * If the target is a channel, the message is sent to all the users in the channel.
 * If the target is a user, the message is sent to that user.
 */
	void	Server::privmsgCommand(const strings& commands, int& cindex)
	{
	// Validate that we have enough parameters
	if (commands.size() < 3)
	{
		clients[cindex].sendMessage(ERR_NEEDMOREPARAMS, clients[cindex].getNickname() + " " + commands[0] + " :Not enough parameters");
		return;
	}

	const std::string& target = commands[1];

	// Extract message arguments from commands, starting from index 2
	std::string message;
	for (size_t i = 2; i < commands.size(); ++i)
	{
		message += commands[i];
		if (i != commands.size() - 1)
		{
			message += " ";
		}
	}

	// Handle Channel Message
	if (target[0] == '#')
	{
		// Check if channel exists
		if (!existsChannel(target))
		{
			clients[cindex].sendMessage(ERR_NOSUCHCHANNEL, clients[cindex].getNickname() + " " + target + " :No such channel");
			return ;
		}

		Channel* channel = getChannels()[target];

		// Check if the user is a member of the channel
		if (!channel->isMember(&clients[cindex]))
		{
			clients[cindex].sendMessage(ERR_CANNOTSENDTOCHAN, clients[cindex].getNickname() + " " + target + " :Cannot send to channel (you're not a member)");
			return;
		}

		// Broadcast the message to all members of the channel except the sender
		channel->privateMessage(clients[cindex].getNickname(), "PRIVMSG", target + " :" + message);
	}
	else
	{
		// Handle Private Message to User
		if (!existsClient(target))
		{
			clients[cindex].sendMessage(ERR_NOSUCHNICK, clients[cindex].getNickname() + " " + target + " :No such nick");
			return;
		}

		Client* recipient = &clients[findClientIndexByNickname(target)];
		recipient->sendMessage(clients[cindex].getNickname(), "PRIVMSG", target + " :" + message);
	}
	}
