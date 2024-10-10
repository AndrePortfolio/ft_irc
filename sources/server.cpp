/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 08:05:47 by apereira          #+#    #+#             */
/*   Updated: 2024/10/10 12:14:19 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

//----------------------------------------------------------------------------//
//--------------------------- Contructors / Destructor -----------------------//
//----------------------------------------------------------------------------//

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
	if (this->port < 1024 || this->port > 65535)
		throw std::runtime_error( "Error: Port must be a number from 1024 to 65535.");
}

/* Configure the server socket, bind to an IP/port, and prepare for client connections */
void	Server::initServer()
{
	// Create TCP socket using IPv4
	socketFd = socket(AF_INET, SOCK_STREAM, DEFAULT_PROTOCOL);
	if (socketFd == ERROR)
		throw std::runtime_error("Error: Failed to Assign socket");

	configureSocketOptions(socketFd);
	setNonBlocking(socketFd);
	initServerAddress();

	if (bind(socketFd, (struct sockaddr*)&address, sizeof(address)) == ERROR)
		throw std::runtime_error("Error: Couldn't bind the IP and port to socket");
	else
		signal = true;

	if (listen(socketFd, MAX_CONNEECTIONS) == ERROR)
		throw std::runtime_error("Error: Failed to listen on the socket");

	std::cout	<< CYAN << "Status: " << RESET << "Server listening on port "
				<< port << "\n";
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

/* Listen for clients wanting to connect to the server and accept them */
void	Server::listenForClients(struct pollfd(&fds)[MAX_CONNEECTIONS], int& activeFds)
{
	// Checks for pending connection requests
	if (fds[0].revents & POLLIN)
	{
		int	clientFd = accept(socketFd, nullptr, nullptr);

		if (clientFd == ERROR)
			throw std::runtime_error("Error: Failed to Assign socket to client");
		else if (clientFd >= 0)
		{
			Client newClient;

			setNonBlocking(clientFd);
			clients.emplace_back(newClient);
			updatePool(fds[activeFds], activeFds, clientFd);

			std::cout << "New client connected: " << clientFd << std::endl;
		}
	}
}

/* Add new file descriptor to the pool */
void	Server::updatePool(struct pollfd& fds, int& activeFds, int socket)
{
	fds.fd = socket;
	fds.events = POLLIN;
	activeFds++;
}

/* Listen indefinitely for Events */
void	Server::checkForEvent(struct pollfd(&fds)[MAX_CONNEECTIONS], int& activeFds)
{
	int	poolCount = poll(fds, activeFds, WAIT_INDEFINITELY);
	if (poolCount == ERROR)
		throw std::runtime_error("Error: pool failed");
}

/* Accept client connections and receive data from them */
void	Server::acceptClients()
{
	struct pollfd	fds[MAX_CONNEECTIONS];
	int				activeFds = 0;

	// Init pool with the server socket
	updatePool(fds[0], activeFds, socketFd);
	while (true)
	{
		checkForEvent(fds, activeFds);
		listenForClients(fds, activeFds);

		for (int i = 1; i < activeFds; i++)
		{
			if (fds[i].revents & POLLIN)
			{
				receivedNewData(fds[i].fd);
				if (fds[i].fd == -1)
				{
					fds[i] = fds[activeFds - 1];
					activeFds--;
				}
			}
		}
	}
}

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

/* Read data from client and output it to the server */
void Server::receivedNewData(int fd)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytesRead = read(fd, buffer, sizeof(buffer) - 1);

	if (bytesRead == ERROR)
		throw std::runtime_error("Error: Failed to read from client socket");
	else if (bytesRead == CLIENT_DISCONNECTED)
	{
		std::cout << "Client" << fd << " disconnected.\n";
		close(fd);
		return ;
	}
	buffer[bytesRead] = '\0';
	std::cout << "Client " << fd << ": " << buffer << std::endl;
}
