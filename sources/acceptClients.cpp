/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acceptClients.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:31:16 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/11/14 12:54:51 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/* Add new file descriptor to the pool */
void	Server::updatePool(pollfd& fds, int& activeFds, int socket)
{
	fds.fd = socket;
	fds.events = POLLIN;
	activeFds++;
}

/* Listen indefinitely for Events */
void	Server::checkForEvent(pollfd(&fds)[MAX_FDS], int& activeFds)
{
	int	poolCount = poll(fds, activeFds, WAIT_INDEFINITELY);
	if (poolCount == ERROR)
		throw std::runtime_error("Error: pool failed");
}

/* Listen for clients wanting to connect to the server and accept them */
void	Server::listenForClients(pollfd(&fds)[MAX_FDS], int& activeFds)
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
		clients[activeFds - 1] = newClient;

		updatePool(fds[activeFds], activeFds, clientSocket);
		printMessage(NEW_CONNECTION, clientSocket - DEFAULT_FDS);
	}
}

/* Checks if there is data to read on the client socket */
void	Server::CheckForClientData(pollfd(&fds)[MAX_FDS], int& activeFds)
{
	for (int i = 1; i < activeFds; i++)
	{
		if (fds[i].revents & POLLIN)
			receivedNewData(fds, i, activeFds);
	}
}

/* Read data from client and output it to the server */
void Server::receivedNewData(pollfd(&fds)[MAX_FDS], int& client, int& activeFds)
{
	char	buffer[BUFFER_SIZE];
	int		bytesRead = recv(fds[client].fd, buffer, sizeof(buffer) - 1, DEFAULT);

	if (bytesRead == ERROR)
		throw std::runtime_error("Error: Failed to read from client socket");
	else if (bytesRead == CLIENT_DISCONNECTED)
	{
		printMessage(DISCONNECTED, fds[client].fd);
		adjustClients(fds, client, activeFds);
		return ;
	}
	buffer[bytesRead] = '\0';
	int	clientIndex = client - 1;
	handleData(buffer, clientIndex, fds, activeFds);
}

/* Removes client from map and makes sure there are no gaps in the pool of fds */
void Server::adjustClients(pollfd(&fds)[MAX_FDS], int i, int& activeFds)
{
	int key = fds[i].fd - DEFAULT_FDS;

	// Remove from `clients` map and adjust keys
	if (clients.find(key) != clients.end()) {
		clients.erase(key);

		// Temporary map to hold adjusted clients
		Clients tempClients;
		int newKey = 0;

		// Reassign keys to be contiguous
		for (clientsIterator it = clients.begin(); it != clients.end(); ++it) {
			tempClients[newKey] = it->second;
			newKey++;
		}

		// Replace the original map with the reordered map
		clients.swap(tempClients);
	}

	// Remove from pool
	close(fds[i].fd);
	for (int j = i; j < activeFds; j++)
		fds[j] = fds[j + 1];
	activeFds--;
}

