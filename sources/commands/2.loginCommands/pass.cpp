/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:38 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/16 14:57:49 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/* checks for the Server password and handles password errors */
std::string	Server::passCommand(const strings& parameters, int& client)
{
	bool	authenticated = clients[client].getStatus();

	if (authenticated == true)
		return (feedbackClient(ERR_ALREADYREGISTERED));
	else if (parameters.size() == 1)
		return (feedbackClient(ERR_NEEDMOREPARAMS));
	// Password can't have spaces, be smaller than 3 chars or bigger than 255
	else if (parameters.size() > 2 || parameters[1].size() < 3 || parameters[1].size() > 255)
		return (feedbackClient(ERR_INVALIDPASSWORD));

	clients[client].setPassword(parameters[1]);
	return ("");	// still unsure if I want to display a message. will decide later
}
