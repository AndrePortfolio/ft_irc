/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:38 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/11/05 10:28:38 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/*
 * The KICK command forcibly removes a user from a channel.
 * It ensures that only authorized operators can execute the kick action,
 * and it notifies both the kicked user and the channel members.
 */
void Server::kickCommand(std::vector<std::string> tokens, Client *client)
{
	// Checks for enough parameters: KICK <channel> <user> [<reason>]
	if (tokens.size() < 3)
	{
		client->sendMessage(ERR_NEEDMOREPARAMS, client->getNickname() + " " + tokens[0] + " :Not enough parameters");
		return;
	}

	if (!existsChannel(tokens[1]))
	{
		client->sendMessage(ERR_NOSUCHCHANNEL, client->getNickname() + " " + tokens[1] + " :No such channel");
		return;
	}

	Channel *channel = channels[tokens[1]];

	if (!existsClient(tokens[2]))
	{
		client->sendMessage(ERR_NOSUCHNICK, client->getNickname() + " " + tokens[2] + " :No such nick");
		return;
	}

	Client *target = clients[client_fds[tokens[2]]];

	if (!channel->isMember(target))
	{
		client->sendMessage(ERR_USERNOTINCHANNEL, client->getNickname() + " " + tokens[2] + " " + tokens[1] + " :is not on channel");
		return;
	}

	if (!channel->isMember(client))
	{
		client->sendMessage(ERR_NOTONCHANNEL, client->getNickname() + " " + tokens[1] + " :You're not on that channel");
		return;
	}

	if (!channel->isOperator(client))
	{
		client->sendMessage(ERR_CHANOPRIVSNEEDED, client->getNickname() + " " + tokens[1] + " :You're not channel operator");
		return;
	}

	// Send the KICK message to the target client and notify other members
	if (tokens.size() == 3)
	{
		// No specific reason provided, use a default message
		channel->sendMessage(client->getNickname(), "KICK", tokens[1] + " " + tokens[2] + " :You have been kicked from channel");
	}
	else
	{
		channel->sendMessage(client->getNickname(), "KICK", tokens[1] + " " + tokens[2] + " :" + tokens[3]);
	}

	// Remove the target client from the channel
	channel->removeClient(target);
}
