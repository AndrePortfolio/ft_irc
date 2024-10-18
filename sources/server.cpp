/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 08:05:47 by apereira          #+#    #+#             */
/*   Updated: 2024/10/18 10:54:10 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

//----------------------------------------------------------------------------//
//--------------------------- Contructors / Destructor -----------------------//
//----------------------------------------------------------------------------//

Server::Server(std::string port, std::string password)
	:	port(),
		password(password),
		signal(false),
		socketFd(-1),
		address(),
		clients()
{
	validateInput(port, password);
	runServer();
}

Server::Server(const Server &copy)
{
	*this = copy;
}

Server::~Server()
{
	if (socketFd >= 0)
		close(socketFd);
}
//----------------------------------------------------------------------------//
//---------------------------------- Operators -------------------------------//
//----------------------------------------------------------------------------//

Server&	Server::operator=(const Server &other)
{
	if (this != &other)
	{
		this->port = other.port;
		this->password = other.password;
		this->signal = other.signal;
		this->socketFd = other.socketFd;
		this->address = other.address;
		this->clients = other.clients;
	}
	return (*this);
}
//----------------------------------------------------------------------------//
//----------------------------------- Methods --------------------------------//
//----------------------------------------------------------------------------//

/* Check for valid ports and existing passowrd */
void	Server::validateInput(std::string port, std::string password)
{
	std::stringstream	portStream(port);

	if (password.empty())
		throw std::runtime_error("Error: no password was provided.");

	if (port.empty())
		throw std::runtime_error("Error: no port was provided.");

	portStream >> this->port;
	if (!portStream.eof())
		throw std::runtime_error("Error: Port must be a valid number");

	if (this->port < MIN_ALLOWED_PORT || this->port > MAX_ALLOWED_PORT)
		throw std::runtime_error( "Error: Port must be a number from 1024 to 65535.");
}

/* Configure the server socket, bind to an IP/port, and prepare for client connections */
void	Server::runServer()
{
	printMessage(SERVER, DEFAULT);

	// Step 1: Create the server socket
	createServerSocket();
	setNonBlocking(socketFd);

	// Step 2: Bind the socket to the IP/port
	initServerAddress();
	bindServerSocket();

	// Step 3: Mark the socket for listening in
	listenToServerSocket();

	// Step 4: Accept incomming connections.
	acceptClients();
}

/* Accept client connections and receive data from them */
void	Server::acceptClients()
{
	struct pollfd	fds[MAX_FDS];
	int				activeFds = 0;

	// Init pool with the server socket
	updatePool(fds[0], activeFds, socketFd);
	while (true)
	{
		checkForEvent(fds, activeFds);
		listenForClients(fds, activeFds);
		CheckForClientData(fds, activeFds);
	}
}

// Check if a channel exists
bool	Server::existsChannel(std::string name) const
{
	if (this->channels.find(name) != this->channels.end())
		return true;
	return false;
}

// Remove a channel from the server by its name
void Server::removeChannel(std::string channel_name)
{
	channels.erase(channel_name);
}

std::vector<std::string> Server::split(std::string str, char c) const
{
	std::vector<std::string> result;
	std::string tmp;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == c)
		{
			result.push_back(tmp);
			tmp.clear();
		}
		else
			tmp += str[i];
	}
	result.push_back(tmp);
	return result;
}

