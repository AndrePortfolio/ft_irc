/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:38 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/11/07 11:30:39 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/*
 * Handles the INVITE command to invite a user to a specific channel.
 * If the user is successfully invited, an INVITE message is sent to the target user.
 * The invitation becomes invalid if the target user joins the channel.
 */
void Server::inviteCommand(const strings& commands, int& cindex)
{
	// Checks for param's (user to invite and channel name)
	bool	authenticated = clients[cindex].getStatus();

	if (authenticated != true)
	{
		std::string outputMsg = feedbackClient(ERR_NOTAUTHENTICATED);
		send(clients[cindex].getSocket(), outputMsg.c_str(), outputMsg.length(), DEFAULT);
		return ;
	}
	if (commands.size() < 3)
	{
		clients[cindex].sendMessage(ERR_NEEDMOREPARAMS, clients[cindex].getNickname() + " " + commands[0] + " :Not enough parameters");
		return;
	}

	if (!existsChannel(commands[2]))
	{
		clients[cindex].sendMessage(ERR_NOSUCHCHANNEL, clients[cindex].getNickname() + " " + commands[2] + " :No such channel");
		return;
	}

	if (!existsClient(commands[1]))
	{
		clients[cindex].sendMessage(ERR_NOSUCHNICK, clients[cindex].getNickname() + " " + commands[1] + " :No such nick");
		return;
	}

	Channel* channel = channels[commands[2]];
	if (!channel->isMember(&clients[cindex]))
	{
		clients[cindex].sendMessage(ERR_NOTONCHANNEL, clients[cindex].getNickname() + " " + commands[2] + " :You're not on that channel");
		return;
	}

	// Check if the user has operator privileges or if the channel is invite-only (+i mode)
	if (!channel->isOperator(&clients[cindex]) && channel->getMode().find('i') != std::string::npos)
	{
		clients[cindex].sendMessage(ERR_CHANOPRIVSNEEDED, clients[cindex].getNickname() + " " + commands[2] + " :You're not channel operator");
		return;
	}

	int targetIndex = findClientIndexByNickname(commands[1]);
	if (targetIndex == -1 || channel->isMember(&clients[targetIndex]))
	{
		clients[cindex].sendMessage(ERR_USERONCHANNEL, clients[cindex].getNickname() + " " + commands[1] + " " + commands[2] + " :is already on channel");
		return;
	}

	// Check if the user is already in the invited list to avoid redundant invitations
    if (channel->isInvited(&clients[targetIndex]))
    {
        clients[cindex].sendMessage(ERR_USERALREADYINVITED, clients[cindex].getNickname() + " " + commands[1] + " " + commands[2] + " :is already invited to the channel");
        return;
    }

	// Send an INVITE message to the target user
	Client* target = &clients[targetIndex];
	target->sendMessage(clients[cindex].getNickname(), "INVITE", commands[1] + " " + commands[2]);
	// Notify the inviter that the invitation has been sent
	clients[cindex].sendMessage(RPL_INVITING, clients[cindex].getNickname() + " " + commands[1] + " " + commands[2]);
	channel->addInvited(target);
}
