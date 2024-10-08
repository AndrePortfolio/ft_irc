/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 08:05:47 by apereira          #+#    #+#             */
/*   Updated: 2024/10/08 17:59:21 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

//----------------------------------------------------------------------------//
//--------------------------- Contructors / Destructor -----------------------//
//----------------------------------------------------------------------------//

Server::Server(){}

Server::Server(std::string port, std::string password)
	: port(0), password(password), signal(false), socketFd(0), address(), clients()
{
	validateInput(port, password);
	initServer();
	acceptClients();
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
		this->socketFd = other.socketFd;
		this->signal = other.signal;
		this->clients = other.clients;
	}
	return (*this);
}
//----------------------------------------------------------------------------//
//----------------------------------- Methods --------------------------------//
//----------------------------------------------------------------------------//

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
	if (this->port < 1024 || this->port > 65535)
		throw std::runtime_error( "Error: Port must be a number from 1024 to 65535.");
}

void	Server::initServer()
{
	socketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketFd < 0)
		throw std::runtime_error("Error: Failed to Assign socket");

	configureSocketOptions(socketFd);
	setNonBlocking(socketFd);
	initServerAddress();

	if (bind(socketFd, (struct sockaddr*)&address, sizeof(address)) < 0)
		throw std::runtime_error("Error: Couldn't bind the IP and port to socket");
	else
		signal = true;

	if (listen(socketFd, MAX_CONNEECTIONS) < 0)
		throw std::runtime_error("Error: Failed to listen on the socket");

	std::cout	<< CYAN << "Status: " << RESET << "Server listening on port "
				<< port << "\n";
}

void	Server::initServerAddress()
{
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
}

void	Server::acceptClients()
{
	struct pollfd	fds[MAX_FDS];
	int				nfds = 1;

	fds[0].fd = socketFd;
	fds[0].events = POLLIN;

	while (true)
	{
		int	poolCount = poll(fds, nfds, -1);
		if (poolCount < 0)
			throw std::runtime_error("Error: pool failed");

		if (fds[0].revents & POLLIN)
		{
			int	clientFd = accept(socketFd, nullptr, nullptr);

			if (clientFd < 0)
				throw std::runtime_error("Error: Failed to Assign socket to client");
			else if (clientFd >= 0)
			{
				setNonBlocking(clientFd);
				Client newClient;
				clients.emplace_back(newClient);
				fds[nfds].fd = clientFd;
				fds[nfds].events = POLLIN;
				nfds++;

				std::cout << "New client connected: " << clientFd << std::endl;
			}
		}
		for (int i = 1; i < nfds; i++)
		{
			if (fds[i].revents & POLLIN)
			{
				receivedNewData(fds[i].fd);
				if (fds[i].fd == -1)
				{
					fds[i] = fds[nfds - 1];
					nfds--;
				}
			}
		}
	}
}

// Used to avoid "Address already in use" error
void Server::configureSocketOptions(int fd)
{
	int	opt = 1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		throw std::runtime_error("Error: Couldn't set socket options (SO_REUSEADDR)");
}

void Server::setNonBlocking(int fd)
{
	int flags = fcntl(fd, F_GETFL, 0);
	if (flags == -1)
		throw std::runtime_error("Error: Unable to get socket flags");

	if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1)
		throw std::runtime_error("Error: Unable to set non-blocking mode");
}

void Server::receivedNewData(int fd)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytesRead = read(fd, buffer, sizeof(buffer) - 1);
	if (bytesRead < 0)
		throw std::runtime_error("Error: Failed to read from client socket");
	else if (bytesRead == 0)
	{
		std::cout << "Client" << fd << " disconnected.\n";
		close(fd);
		return ;
	}
	buffer[bytesRead] = '\0';
	std::cout << "Client " << fd << ": " << buffer << std::endl;
}
