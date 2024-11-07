/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:38 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/11/07 11:30:34 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/*
 * The KICK command forcibly removes a user from a channel.
 * It ensures that only authorized operators can execute the kick action,
 * and it notifies both the kicked user and the channel members.
 */
void Server::kickCommand(std::vector<std::string> tokens, int& cindex)
{
	bool	authenticated = clients[cindex].getStatus();

	if (authenticated != true)
	{
		std::string outputMsg = feedbackClient(ERR_NOTAUTHENTICATED);
		send(clients[cindex].getSocket(), outputMsg.c_str(), outputMsg.length(), DEFAULT);
		return ;
	}
	// Checks for enough parameters: KICK <channel> <user> [<reason>]
	if (tokens.size() < 3)
	{
		clients[cindex].sendMessage(ERR_NEEDMOREPARAMS, clients[cindex].getNickname() + " " + tokens[0] + " :Not enough parameters");
		return;
	}

	if (!existsChannel(tokens[1]))
	{
		clients[cindex].sendMessage(ERR_NOSUCHCHANNEL, clients[cindex].getNickname() + " " + tokens[1] + " :No such channel");
		return;
	}

	Channel *channel = channels[tokens[1]];

	if (!existsClient(tokens[2]))
	{
		clients[cindex].sendMessage(ERR_NOSUCHNICK, clients[cindex].getNickname() + " " + tokens[2] + " :No such nick");
		return;
	}

	Client *target = &clients[findClientIndexByNickname(tokens[2])];

	if (!channel->isMember(target))
	{
		clients[cindex].sendMessage(ERR_USERNOTINCHANNEL, clients[cindex].getNickname() + " " + tokens[2] + " " + tokens[1] + " :is not on channel");
		return;
	}

	if (!channel->isMember(&clients[cindex]))
	{
		clients[cindex].sendMessage(ERR_NOTONCHANNEL, clients[cindex].getNickname() + " " + tokens[1] + " :You're not on that channel");
		return;
	}

	if (!channel->isOperator(&clients[cindex]))
	{
		clients[cindex].sendMessage(ERR_CHANOPRIVSNEEDED, clients[cindex].getNickname() + " " + tokens[1] + " :You're not channel operator");
		return;
	}

	// Send the KICK message to the target client and notify other members
	if (tokens.size() == 3)
	{
		// No specific reason provided, use a default message
		channel->sendMessage(clients[cindex].getNickname(), "KICK", tokens[1] + " " + tokens[2] + " :You have been kicked from channel");
	}
	else
	{
		// Use the provided reason for the kick
		channel->sendMessage(clients[cindex].getNickname(), "KICK", tokens[1] + " " + tokens[2] + " :" + tokens[3]);
	}

	// Remove the target client from the channel
	channel->removeClient(target);
}
