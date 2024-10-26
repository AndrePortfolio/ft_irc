/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:38 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/26 14:00:25 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/* Terminates the client's connection to the server */
std::string	Server::quitCommand(const strings& parameters, int& client)
{
	// if joined channels inform clients from that channel

	// if no channels, just send the message in the server

	// remove client from clients array, sitll need to know if I need to free something
	// adjustClients(fds, client, activeFds);

	(void)parameters;
	(void)client;
	return ("");
}
