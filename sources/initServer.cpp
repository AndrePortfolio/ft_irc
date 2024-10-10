/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:31:22 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/10 12:34:06 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/* Used to avoid "Address already in use" error */
void Server::configureSocketOptions(int fd)
{
	int	opt = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == ERROR)
		throw std::runtime_error("Error: Couldn't set socket options (SO_REUSEADDR)");
}

/* If I/O operations aren't ready it returns immediately,allowing the program to keep running */
void Server::setNonBlocking(int fd)
{
	// Gets the current flags from the file descriptor
	int flags = fcntl(fd, F_GETFL, 0);
	if (flags == ERROR)
		throw std::runtime_error("Error: Unable to get socket flags");

	// Set flags to include non-blocking mode
	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == ERROR)
		throw std::runtime_error("Error: Unable to set non-blocking mode");
}

/* Configure the sockaddr_in structure with the server address and port */
void	Server::initServerAddress()
{
	// Use IPv4 protocol
	address.sin_family = AF_INET;

	// Bind to all available network interfaces (0.0.0.0)
	address.sin_addr.s_addr = INADDR_ANY;

	// Set the port number, converting to network byte order
	address.sin_port = htons(port);
}
