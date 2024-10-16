/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:38 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/16 11:20:56 by apereira         ###   ########.fr       */
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
	if (commands[1] == "0")
	{
		for (t_channelIterator it = channels.begin(); it != channels.end(); it++)
		{
			if (it->second->isMember(&clients[cindex]))
			{
				std::vector<std::string> partTokens;

				partTokens.push_back("PART");
				partTokens.push_back(it->second->getName());
				partCommand(partTokens, cindex);
			}
		}
		clients[cindex].setNbChannels(0);
		return;
	}
	// std::vector<std::string> channel_names = split(commands[1], ',');
	// std::vector<Channel *> channels_to_sub;
	// for (
	// 	std::vector<std::string>::iterator it_names = channel_names.begin();
	// 	it_names != channel_names.end();
	// 	it_names++
	// 	)
	// {
	// 	if (*it_names == "#" || (*it_names)[0] != '#' || it_names->find(',') != std::string::npos || it_names->find(' ') != std::string::npos || it_names->find('\x07') != std::string::npos)
	// 	{
	// 		clients[cindex].sendMessage(ERR_BADCHANMASK,*it_names + " :Cannot join channel: Channel must start with # and cannot contain spaces, commas or \\x07");
	// 		continue ;
	// 	}
	// 	if (clients[cindex].getNbChannels() >= this->config->getChanlimit())
	// 	{
	// 		clients[cindex].sendMessage(ERR_TOOMANYCHANNELS, clients[cindex].getNickname() + " " + *(it_names) + " :You have joined too many channels");
	// 		continue ;
	// 	}
	// 	if (existsChannel(*it_names))
	// 	{
	// 		channels_to_sub.push_back(this->getChannels()[*it_names]);
	// 	}
	// 	else
	// 	{
	// 		Channel *channel_to_add = new Channel("", *it_names, client);
	// 		channel_to_add->addClient(clients[-1]);
	// 		channels_to_sub.push_back(channel_to_add);
	// 		channels[*it_names] = channel_to_add;
	// 	}
	// }
}

