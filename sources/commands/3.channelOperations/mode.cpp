/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:38 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/29 08:33:17 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/*
 * The MODE command is used to set or view the user or channel mode.
 * If the target is a channel and the mode changes, the message is sent to all the users in the channel.
 */
void Server::modeCommand(const strings& commands, int& cindex)
{
	if (commands.size() < 2)
	{
		clients[cindex].sendMessage(ERR_NEEDMOREPARAMS, clients[cindex].getNickname() + " " + commands[0] + " :Not enough parameters");
		return;
	}

	// Handle channel mode changes
	if (commands[1][0] == '#')
	{
		// Check if the channel exists
		if (!existsChannel(commands[1]))
		{
			clients[cindex].sendMessage(ERR_NOSUCHCHANNEL, clients[cindex].getNickname() + " " + commands[1] + " :No such channel");
			return;
		}

		Channel *channel = this->getChannels()[commands[1]];

		// If only the channel name is provided, return the current mode
		if (commands.size() == 2)
		{
			clients[cindex].sendMessage(RPL_CHANNELMODEIS, clients[cindex].getNickname() + " " + commands[1] + " " + channel->getMode());
			return;
		}

		// Check if the user is a channel operator
		if (!channel->isOperator(&clients[cindex]))
		{
			clients[cindex].sendMessage(ERR_CHANOPRIVSNEEDED, clients[cindex].getNickname() + " " + commands[1] + " :You're not channel operator");
			return;
		}

		// Iterate through mode changes to validate characters
		for (size_t i = 0; i < commands[2].size(); i++)
		{
			if (commands[2][i] != '+' && commands[2][i] != '-' && commands[2][i] != 'i' && commands[2][i] != 't')
			{
				clients[cindex].sendMessage(ERR_UNKNOWNMODE, clients[cindex].getNickname() + " " + commands[2][i] + " :is unknown mode char to me");
				return;
			}
		}

		// Update channel mode and notify users
		std::string to_send;
		std::string buffer_add;
		std::string buffer_del;

		size_t argIndex = 3; // Arguments start after commands[2] (modes)
		for (size_t i = 0; i < commands[2].size(); i++)
		{
			char modeChar = commands[2][i];

			if (modeChar == '+' || modeChar == '-')
				continue;

			bool addMode = (commands[2][i - 1] == '+');

			switch (modeChar)
			{
				case 'i': // Invite-only mode
					if (addMode)
						buffer_add += channel->addMode("i");
					else
						buffer_del += channel->delMode("i");
					break;

				case 't': // Topic settable only by operators
					if (addMode)
						buffer_add += channel->addMode("t");
					else
						buffer_del += channel->delMode("t");
					break;

				// case 'k': // Key (password) mode
				// 	if (addMode)
				// 	{
				// 		if (commands.size() > argIndex)
				// 		{
				// 			channel->setPassword(commands[argIndex++]);
				// 			buffer_add += "k";
				// 		}
				// 		else
				// 		{
				// 			clients[cindex].sendMessage(ERR_NEEDMOREPARAMS, clients[cindex].getNickname() + " " + commands[0] + " :Not enough parameters for +k");
				// 			return;
				// 		}
				// 	}
				// 	else
				// 	{
				// 		channel->removePassword();
				// 		buffer_del += "k";
				// 	}
				// 	break;

				case 'o': // Operator mode
					if (addMode)
					{
						if (commands.size() > argIndex)
						{
							std::string targetNick = commands[argIndex++];
							int targetIndex = findClientIndexByNickname(targetNick);
							if (targetIndex != -1)
							{
								if (channel->addOperator(&clients[targetIndex]))
									buffer_add += "o";
							}
							else
								clients[cindex].sendMessage(ERR_NOSUCHNICK, clients[cindex].getNickname() + " " + targetNick + " :No such nick");
						}
						else
						{
							clients[cindex].sendMessage(ERR_NEEDMOREPARAMS, clients[cindex].getNickname() + " " + commands[0] + " :Not enough parameters for +o");
							return;
						}
					}
					else
					{
						if (commands.size() > argIndex)
						{
							std::string targetNick = commands[argIndex++];
							if (channel->removeOperator(&clients[findClientIndexByNickname(targetNick)]))
								buffer_del += "o";
							else
								clients[cindex].sendMessage(ERR_NOSUCHNICK, clients[cindex].getNickname() + " " + targetNick + " :No such nick");
						}
						else
						{
							clients[cindex].sendMessage(ERR_NEEDMOREPARAMS, clients[cindex].getNickname() + " " + commands[0] + " :Not enough parameters for -o");
							return;
						}
					}
					break;

				case 'l': // Limit mode
					if (addMode)
					{
						if (commands.size() > argIndex)
						{
							int limit = std::stoi(commands[argIndex++]);
							channel->setUserLimit(limit);
							buffer_add += "l";
						}
						else
						{
							clients[cindex].sendMessage(ERR_NEEDMOREPARAMS, clients[cindex].getNickname() + " " + commands[0] + " :Not enough parameters for +l");
							return;
						}
					}
					else
					{
						channel->removeUserLimit();
						buffer_del += "l";
					}
					break;

				default:
					clients[cindex].sendMessage(ERR_UNKNOWNMODE, clients[cindex].getNickname() + " " + modeChar + " :is unknown mode char to me");
					return;
			}
		}

		// Construct the mode change message (example: +it-m)
		if (buffer_add != "")
		{
			to_send += "+" + buffer_add;
		}
		if (buffer_del != "")
		{
			to_send += "-" + buffer_del;
		}
		// Send the mode change message to all users in the channel
		channel->sendMessage(clients[cindex].getNickname(), "MODE", commands[1] + " " + to_send);
	}
	else
	{
		// Check if the user exists
		if (!existsClient(commands[1]))
		{
			clients[cindex].sendMessage(ERR_NOSUCHNICK, clients[cindex].getNickname() + " " + commands[1] + " :No such nick");
			return;
		}
		Client *target = nullptr;
		// Find the target client by nickname
		for (Clients::iterator it = clients.begin(); it != clients.end(); ++it)
		{
			if (it->second.getNickname() == commands[1])
			{
				target = &it->second;
				break;
			}
		}
		// Check if the target client matches the requesting client
		if (target->getNickname() != commands[1])
		{
			clients[cindex].sendMessage(ERR_USERSDONTMATCH, clients[cindex].getNickname() + " :Cant change mode for other users");
			return;
		}
		// If only the nickname is provided, return the current user mode
		if (commands.size() == 2)
		{
			clients[cindex].sendMessage(RPL_UMODEIS, clients[cindex].getNickname() + " :" + target->getMode());
			return;
		}
	}
}
