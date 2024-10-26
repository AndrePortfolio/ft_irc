/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:38 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/26 11:18:23 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/* Unsure of what this does, just replicating behavior from previous code */
std::string	Server::userCommand(const strings& parameters, int& client)
{
	std::string	username;
	std::string	realname;
	bool		authenticated = clients[client].getStatus();

	if (authenticated == true)
		return (feedbackClient(ERR_ALREADYREGISTERED));
	else if (parameters.size() != 5 || parameters[1].size() < 1)
		return (feedbackClient(ERR_NEEDMOREPARAMS));
	else if ((parameters[2] != "0" && parameters[2] != "*") || parameters[3] != "*")
		return (feedbackClient(ERR_UNKNOWNCOMMAND));
	else if (parameters[1].size() > USERLEN)
		username = parameters[1].substr(0, USERLEN);
	else
		username = parameters[1];

	realname = parameters[4];
	clients[client].setUsername(username);
	clients[client].setRealname(realname);
	clients[client].setStatus(true);
	return (getMessage(USERNAME_SUCCESS, client));
}
