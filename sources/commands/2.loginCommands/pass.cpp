/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:38 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/16 12:54:29 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

std::string Server::feedbackClient(int input, int& i, const strings& parameters)
{
	std::string msg;
	std::string command = parameters[0];

	switch (input)
	{
		case 461:
			msg.append(clients[i].getNickname());
			msg.append(" ");
			msg.append(command);
			msg.append(" :Not enough parameters\n");
			return (msg);
		case 462:
			msg.append(clients[i].getNickname());
			msg.append(" :You may not reregister\n");
			return (msg);
		default:
			return (msg);
	}
}

/* Unsure of what this does, just replicating behavior from previous code */
std::string	Server::passCommand(const strings& parameters, int& client)
{
	bool	authenticated = clients[client].getStatus();
	int		clientSocket = clients[client].getSocket();

	std::cout << authenticated << clientSocket << std::endl;

	if (authenticated == true)
		return (feedbackClient(ERR_ALREADYREGISTERED, client, parameters));
	else if (parameters.size() == 1)
		return (feedbackClient(ERR_NEEDMOREPARAMS, client, parameters));
	else
	{
		clients[client].setPassword(parameters[1]);
		clients[client].setStatus(true);
	}
	return (":server 001 * :Password accepted\r\n");
}
