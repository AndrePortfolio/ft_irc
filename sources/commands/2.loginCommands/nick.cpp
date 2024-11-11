/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:38 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/11/11 11:38:38 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/* Sets the client nickname or displays changes to all clients */
std::string	Server::nickCommand(const strings& parameters, int& client)
{
	std::string	nickname;
	bool		passwordAssigned = !clients[client].getPassword().empty();

	if (!passwordAssigned)
		return (feedbackClient(ERR_NOTAUTHENTICATED));
	else if (parameters.size() == 1)
		return (feedbackClient(ERR_NONICKNAMEGIVEN));
	else if (parameters.size() > 2 || invalidChars(parameters[1]))
		return (feedbackClient(ERR_ERRONEUSNICKNAME));
	else
	{
		for (size_t i = 0; i < clients.size(); i++)
			if (parameters[1] == clients[i].getNickname())
				return (feedbackClient(ERR_NICKNAMEINUSE));
	}
	nickname = parameters[1];
	informOtherClients(client, nickname);
	clients[client].setNickname(nickname);
	return (getMessage(NICKNAME_SUCCESS, client));
}

bool	Server::invalidChars(std::string nick)
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
