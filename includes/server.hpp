/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:32:24 by andre-da          #+#    #+#             */
/*   Updated: 2024/10/11 12:52:20 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "headers.hpp"

class Client;

class Server
{
	private:
		int					port;
		std::string			password;
		bool				signal;
		int					socketFd;
		struct sockaddr_in	address;
		std::vector<Client>	clients;

		Server(){}
		Server(const Server &copy);
		Server& operator=(const Server &other);

	public:
		Server(std::string port, std::string password);
		~Server();

		void	validateInput(std::string port, std::string password);
		void	runServer();
		void	createServerSocket();
		void	setNonBlocking(int& fd);
		void	initServerAddress();
		void	bindServerSocket();
		void	listenToServerSocket();
		void	acceptClients();
		void	updatePool(struct pollfd& fds, int& activeFds, int socket);
		void	checkForEvent(struct pollfd(&fds)[MAX_FDS], int& activeFds);
		void	listenForClients(struct pollfd(&fds)[MAX_FDS], int& activeFds);
		void	CheckforClientData(struct pollfd(&fds)[MAX_FDS], int& activeFds);
		void	receivedNewData(int fd);
};

#endif
