/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:38 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/31 09:31:40 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/* Unsure of what this does, just replicating behavior from previous code */
std::string	Server::operCommand(const strings& parameters, int& client)
{
	std::string	nickname;
	std::string	pass;
	bool		authenticated = clients[client].getStatus();
	Operators	authorizeOps;
	std::string	localhost = "127.0.0.1";
	char*		clientAddress = inet_ntoa(((sockaddr_in*)&clients[client].getAddress())->sin_addr);

	authorizeOps.push_back(std::make_pair("admin", "secretpassword"));
	authorizeOps.push_back(std::make_pair("operator1", "password1"));

	if (authenticated != true)
		return (feedbackClient(ERR_NOTAUTHENTICATED));
	else if (parameters.size() != 3)
		return (feedbackClient(ERR_NEEDMOREPARAMS));
	nickname = parameters[1];
	pass = parameters[2];

	for (opIterator it = authorizeOps.begin(); it != authorizeOps.end(); it++)
	{
		if (it->first == nickname)
		{
			if (it->second != pass)
				return (feedbackClient(ERR_PASSWDMISMATCH));
			else if (strcmp(clientAddress, localhost.c_str()) != 0)
				return (feedbackClient(ERR_NOOPERHOST));
			else
				clients[client].setOperator(true);
			break ;
		}
	}
	return (feedbackClient(RPL_YOUAREOPER));
}
