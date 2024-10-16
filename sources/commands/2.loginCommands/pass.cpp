/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:38 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/16 13:26:42 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/* checks for the Server password and handles password errors */
std::string	Server::passCommand(const strings& parameters, int& client)
{
	bool	authenticated = clients[client].getStatus();

	if (authenticated == true)
		return (feedbackClient(ERR_ALREADYREGISTERED, client, parameters));
	else if (parameters.size() == 1)
		return (feedbackClient(ERR_NEEDMOREPARAMS, client, parameters));
	else
	{
		if (parameters.size() > 2)
			clients[client].setPassword("");
		else
			clients[client].setPassword(parameters[1]);
	}
	return ("");
}
