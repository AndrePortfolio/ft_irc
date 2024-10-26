/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:38 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/26 15:07:00 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/* Terminates the client's connection to the server, sending a message to all channels */
std::string	Server::quitCommand(const strings& parameters, int& client, pollfd(&fds)[MAX_FDS])
{
	bool 		joined_channel = false;
	int			activeFds = clients.size() + 1; // add the server fd
	std::string	reason;

	if (parameters.size() == 1)
		reason = "";
	else
		reason = parameters[1];

	if (joined_channel)	// send ":nick QUIT <reason>"" to all clients in the same channel
	{
		/* code */
	}
	printMessage(DISCONNECTED, fds[client + 1].fd);
	adjustClients(fds, client + 1, activeFds);
	return ("");
}
