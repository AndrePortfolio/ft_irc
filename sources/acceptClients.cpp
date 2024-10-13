/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acceptClients.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:31:16 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/13 14:00:10 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/* Add new file descriptor to the pool */
void	Server::updatePool(struct pollfd& fds, int& activeFds, int socket)
{
	fds.fd = socket;
	fds.events = POLLIN;
	activeFds++;
}

/* Listen indefinitely for Events */
void	Server::checkForEvent(struct pollfd(&fds)[MAX_FDS], int& activeFds)
{
	int	poolCount = poll(fds, activeFds, WAIT_INDEFINITELY);
	if (poolCount == ERROR)
		throw std::runtime_error("Error: pool failed");
}

/* Listen for clients wanting to connect to the server and accept them */
void	Server::listenForClients(struct pollfd(&fds)[MAX_FDS], int& activeFds)
{
	// Checks for pending connection requests
	if (fds[0].revents & POLLIN)
	{
		sockaddr_in	clientAddress;
		int			clientSocket;
		socklen_t	clientSize = sizeof(clientAddress);

		clientSocket = accept(socketFd, (sockaddr*)&clientAddress, &clientSize);
		if (clientSocket == ERROR)
			throw std::runtime_error("Error: Failed to Assign socket to client");
		setNonBlocking(clientSocket);

		Client	newClient(clientSocket, clientAddress);
		clients[clientSocket - DEFAULT_FDS] = newClient;

		updatePool(fds[activeFds], activeFds, clientSocket);
		printMessage(NEW_CONNECTION, clientSocket - DEFAULT_FDS);
	}
}

/* Checks if there is data to read on the client socket */
void	Server::CheckForClientData(struct pollfd(&fds)[MAX_FDS], int& activeFds)
{
	for (int i = 1; i < activeFds; i++)
	{
		if (fds[i].revents & POLLIN)
			receivedNewData(fds, i, activeFds);
	}
}

/* Read data from client and output it to the server */
void Server::receivedNewData(struct pollfd(&fds)[MAX_FDS], int& client, int& activeFds)
{
	char	buffer[BUFFER_SIZE];
	int		bytesRead = recv(fds[client].fd, buffer, sizeof(buffer) - 1, 0);

	if (bytesRead == ERROR)
		throw std::runtime_error("Error: Failed to read from client socket");
	else if (bytesRead == CLIENT_DISCONNECTED)
	{
		printMessage(DISCONNECTED, fds[client].fd);
		adjustClients(fds, client, activeFds);
		return ;
	}
	buffer[bytesRead] = '\0';
	handleData(buffer, client);
}

/* Removes client from map and makes sure there are no gaps in the pool of fds */
void Server::adjustClients(struct pollfd(&fds)[MAX_FDS], int& client, int& activeFds)
{
	int key = fds[client].fd - DEFAULT_FDS;

	// Remove from map
	if (clients.find(key) != clients.end())
		clients.erase(key);

	// Remove from pool
	close(fds[client].fd);
	for (int j = client; j < activeFds; j++)
		fds[j] = fds[j + 1];
	activeFds--;
}

/* Removes ENTER from the command, prepares for parsing and outputs to client */
void	Server::handleData(char	buffer[BUFFER_SIZE], int& client)
{
	std::string	message(buffer, strlen(buffer) - 1);
	if (message.back() == '\r')
		message.erase(message.end() - 1);

	std::string	outputMsg = parseClientMessage(message, client);
	feebackClient(outputMsg);
}

/* Parses client input */
std::string Server::parseClientMessage(std::string message, int& client)
{
	if (message == "HELP")
	{}
	else if (message == "PASS")
	{}
	else if (message == "NICK")
	{}
	else if (message == "USER")
	{}
	else if (message == "OPER")
	{}
	else if (message == "JOIN")
	{}
	else if (message == "PRIVMSG")
	{}
	else if (message == "KICK")
	{}
	else if (message == "INVITE")
	{}
	else if (message == "TOPIC")
	{}
	else if (message == "MODE")
	{}
	else if (message == "QUIT")
	{}
	else
		return ("Invalid command\n");

	(void)client;
	return (nullptr); // remove after all commands done
}

/* Sends feedback to client */
void	Server::feebackClient(std::string outputMsg)
{
	(void)outputMsg;
}
