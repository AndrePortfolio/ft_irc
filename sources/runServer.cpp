/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:31:22 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/13 11:18:15 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/* Create server socket with the specified options */
void Server::createServerSocket()
{
	// Create TCP socket using IPv4
	socketFd = socket(AF_INET, SOCK_STREAM, DEFAULT);
	if (socketFd == ERROR)
		throw std::runtime_error("Error: Failed to Assign socket");

	// Used to avoid "Address already in use" error
	int	opt = 1;
	if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == ERROR)
		throw std::runtime_error("Error: Couldn't set socket options (SO_REUSEADDR)");
}

/* Returns immediately if no I/O, allowing the program to keep running */
void Server::setNonBlocking(int& fd)
{
	if (fcntl(fd, F_SETFL, O_NONBLOCK) == ERROR)
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

/* Bind the IP and port to the server socket */
void	Server::bindServerSocket()
{
	if (bind(socketFd, (struct sockaddr*)&address, sizeof(address)) == ERROR)
		throw std::runtime_error("Error: Couldn't bind the IP and port to socket");
	else
		signal = true;
}

/* Listen to the socket */
void	Server::listenToServerSocket()
{
	if (listen(socketFd, MAX_CONNECTIONS) == ERROR)
		throw std::runtime_error("Error: Failed to listen on the socket");

	printMessage(LISTENING, DEFAULT);
}
