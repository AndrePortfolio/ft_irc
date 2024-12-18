/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 08:05:47 by apereira          #+#    #+#             */
/*   Updated: 2024/11/20 09:41:29 by apereira         ###   ########.fr       */
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
}

Server::Server(const Server &copy)
{
	*this = copy;
}

Server::~Server()
{
	if (socketFd >= 0)
		close(socketFd);

	// Iterate over all channels and delete them to free memory
	for (t_channelIterator it = channels.begin(); it != channels.end(); ++it)
		delete it->second;
	
	channels.clear();

	for (Clients::iterator it = clients.begin(); it != clients.end(); ++it)
    {
        int clientSocket = it->second.getSocket();
        if (clientSocket >= 0)
            close(clientSocket);
    }
    clients.clear();
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
	if (password.find(' ') != std::string::npos)
		throw std::runtime_error("Error: password can't contain spaces.");

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
	pollfd	fds[MAX_FDS];
	int		activeFds = 0;

	// // Initialize fds array to prevent uninitialized reads.
	for (int i = 0; i < MAX_FDS; i++)
	{
		fds[i].fd = -1;
		fds[i].events = 0;
		fds[i].revents = 0;
	}
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

// Check if a client exists by nickname
bool Server::existsClient(const std::string& name) const
{
	for (Clients::const_iterator it = clients.begin(); it != clients.end(); ++it)
	{
		if (it->second.getNickname() == name)
		{
			return (true);
		}
	}
	return (false);
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

char  Server::closestPlusMinus(const std::string &str, const char &mode) const
{
	//reverse find to get the last occurence of the mode and the closest + or -
	size_t lastMode = str.rfind(mode);
	if (lastMode == std::string::npos)
		return ('\0');

	size_t closestPlus = str.rfind('+', lastMode);
	size_t closestMinus = str.rfind('-', lastMode);
	//if neither is found, default is +
	if (closestPlus == std::string::npos && closestMinus == std::string::npos)
		return '+';
	if (closestPlus == std::string::npos)
		return '-';
	if (closestMinus == std::string::npos)
		return '+';
	// if the last occurence of the mode is closer to + than -
	if (closestPlus > closestMinus)
		return '+';
	return '-';
}

// Returns -1 if client is not found, otherwise returns the index of the client in the map
int Server::findClientIndexByNickname(const std::string& nickname) const
{
	for (Clients::const_iterator it = clients.begin(); it != clients.end(); ++it)
	{
		if (it->second.getNickname() == nickname)
		{
			return it->first; // Return the index/key of the client in the map
		}
	}
	return -1; // Return -1 if client is not found
}
