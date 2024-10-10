/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:32:24 by andre-da          #+#    #+#             */
/*   Updated: 2024/10/10 12:43:32 by andrealbuqu      ###   ########.fr       */
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

		void		validateInput(std::string port, std::string password);
		void		initServer();
		void		initServerAddress();
		void		setNonBlocking(int& fd);
		void		createServerSocket();
		void		acceptClients();
		void		bindServerSocket();
		void		listenToServerSocket();
		void		receivedNewData(int fd);
		void		updatePool(struct pollfd& fds, int& activeFds, int socket);
		void		listenForClients(struct pollfd(&fds)[MAX_CONNEECTIONS], int& activeFds);
		void		checkForEvent(struct pollfd(&fds)[MAX_CONNEECTIONS], int& activeFds);
		void		CheckforClientData(struct pollfd(&fds)[MAX_CONNEECTIONS], int& activeFds);

		static void	signalHandler(int signum);
};

#endif
