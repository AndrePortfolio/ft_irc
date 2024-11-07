/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:38 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/11/07 11:06:22 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/* Terminates the client's connection to the server, sending a message to all channels */
std::string	Server::quitCommand(const strings& parameters, int& client, pollfd(&fds)[MAX_FDS], int& activeFds)
{
	std::string	reason;

	if (parameters.size() == 1)
		reason = "";
	else
		reason = parameters[1];

	if (clients[client].getNbChannels() > 0)	// send ":nick QUIT <reason>"" to all clients in the same channels
	{
		for (t_channelIterator it = channels.begin(); it != channels.end(); ++it)
		{
			Channel* channel = it->second;

			if (channel->isMember(&clients[client]))
				std::cout << "Channel name: " << it->first << std::endl;
		}

	}
	// Send message before disconnecting client
	std::string outputMsg = feedbackClient(ERROR);

	send(clients[client].getSocket(), outputMsg.c_str(), outputMsg.length(), DEFAULT);
	printMessage(DISCONNECTED, fds[client + 1].fd);
	adjustClients(fds, client + 1, activeFds);
	return ("");
}
