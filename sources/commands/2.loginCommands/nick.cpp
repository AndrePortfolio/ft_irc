/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:38 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/16 15:12:47 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

static bool	invalidChars(std::string nick);

/* Sets the client nickname or displays changes to all clients */
std::string	Server::nickCommand(const strings& parameters, int& client)
{
	bool	passwordAssigned = !clients[client].getPassword().empty();

	if (!passwordAssigned)
		return (feedbackClient(ERR_NOTAUTHENTICATED));
	else if (parameters.size() == 1)
		return (feedbackClient(ERR_NONICKNAMEGIVEN));
	else if (parameters.size() > 2 || invalidChars(parameters[1]))
		return (feedbackClient(ERR_ERRONEUSNICKNAME));
	else
	{
		for (size_t i = 0; i < clients.size(); i++)
		{
			if (parameters[1] == clients[i].getNickname())
				return (feedbackClient(ERR_NICKNAMEINUSE));
		}
	}
	clients[client].setNickname(parameters[1]);
	return ("");	// still unsure if I want to display a message. will decide later
}

static bool	invalidChars(std::string nick)
{
	int	foundAlphaNumeric = 0;

	// First char needs to be a letter, and there can't be '\n' or '\r' in nick
	if (!isalpha(nick[0]) || nick.find('\n') != std::string::npos
		|| nick.find('\r') != std::string::npos)
		return  (true);

	// There are at least 3 alphanumeric chars and there can't be any non printable
	for (size_t i = 0; i < nick.length(); ++i)
	{
		if (nick[i] >= 0 && nick[i] <= 32)
			return (true);
		if (isalnum(nick[i]))
			foundAlphaNumeric++;
	}
	if (foundAlphaNumeric < 3)
		return (true);
	return (false);
}
