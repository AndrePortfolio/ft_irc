/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:38 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/26 13:40:39 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

static std::string	pong(std::string token);

/* Checks if the other side of the connection is still connected */
std::string	Server::pingCommand(const strings& parameters, int& client)
{
	bool	authenticated = clients[client].getStatus();

	if (authenticated != true)
		return (feedbackClient(ERR_NOTAUTHENTICATED));
	else if (parameters.size() != 2)
		return (feedbackClient(ERR_NEEDMOREPARAMS));
	return (pong(parameters[1]));
}

/* Server responds to the client with pong + token */
static std::string	pong(std::string token)
{
	std::string msg;

	msg.append(CYAN);
	msg.append("PONG ");
	msg.append(RESET);
	msg.append(token);
	msg.append("\n");
	return (msg);
}
