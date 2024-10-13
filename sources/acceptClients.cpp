/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acceptClients.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:31:16 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/13 08:54:09 by andrealbuqu      ###   ########.fr       */
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
		struct sockaddr_in	clientAddress;
		int					clientSocket;
		socklen_t			clientSize = sizeof(clientAddress);

		clientSocket = accept(socketFd, (sockaddr*)&clientAddress, &clientSize);
		if (clientSocket == ERROR)
			throw std::runtime_error("Error: Failed to Assign socket to client");
		setNonBlocking(clientSocket);

		Client	newClient(clientSocket, clientAddress);

		clients.push_back(newClient);
		updatePool(fds[activeFds], activeFds, clientSocket);
		printMessage(NEW_CONNECTION, DEFAULT);
	}
}

/* Checks if there is data to read on the client socket */
void	Server::CheckforClientData(struct pollfd(&fds)[MAX_FDS], int& activeFds)
{
	for (int i = 1; i < activeFds; i++)
	{
		if (fds[i].revents & POLLIN)
			receivedNewData(fds, i, activeFds);
	}
}

/* Read data from client and output it to the server */
void Server::receivedNewData(struct pollfd(&fds)[MAX_FDS], int& i, int& activeFds)
{
	char	buffer[BUFFER_SIZE];
	int		bytesRead = recv(fds[i].fd, buffer, sizeof(buffer) - 1, 0);

	if (bytesRead == ERROR)
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return ;
		throw std::runtime_error("Error: Failed to read from client socket");
	}
	else if (bytesRead == CLIENT_DISCONNECTED)
	{
		printMessage(DISCONNECTED, fds[i].fd);
		close(fds[i].fd);
		fds[i] = fds[activeFds - 1];
		activeFds--;
		return ;
	}
	buffer[bytesRead] = '\0';
}
