/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:32:24 by andre-da          #+#    #+#             */
/*   Updated: 2024/10/13 13:34:18 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "headers.hpp"

class Client;
typedef std::map<int, Client> Clients;

class Server
{
	private:
		int			port;
		std::string	password;
		bool		signal;
		int			socketFd;
		sockaddr_in	address;
		Clients		clients;

	// Contructors
		Server(){}
		Server(const Server &copy);

	// Operator
		Server& operator=(const Server &other);

	// Member Functions
		void		validateInput(std::string port, std::string password);
		void		runServer();
		void		createServerSocket();
		void		setNonBlocking(int& fd);
		void		initServerAddress();
		void		bindServerSocket();
		void		listenToServerSocket();
		void		acceptClients();
		void		updatePool(struct pollfd& fds, int& activeFds, int socket);
		void		checkForEvent(struct pollfd(&fds)[MAX_FDS], int& activeFds);
		void		listenForClients(struct pollfd(&fds)[MAX_FDS], int& activeFds);
		void		CheckForClientData(struct pollfd(&fds)[MAX_FDS], int& activeFds);
		void		receivedNewData(struct pollfd(&fds)[MAX_FDS], int& client, int& activeFds);
		void		adjustClients(struct pollfd(&fds)[MAX_FDS], int& i, int& activeFds);
		std::string	parseClientMessage(char	buffer[BUFFER_SIZE], int& client);
		void		feebackClient(std::string outputMsg);

	// Util Functions
		std::string			welcomeMsg() const;
		const std::string	currentDateTime();
		void				printMessage(int msg, int index);

	public:
		Server(std::string port, std::string password);
		~Server();
};

#endif
