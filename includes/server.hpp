/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:32:24 by andre-da          #+#    #+#             */
/*   Updated: 2024/10/15 12:11:14 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "headers.hpp"

class Client;

typedef std::map<int, Client> Clients;
typedef std::vector<std::string> strings;
typedef std::vector<std::string>::const_iterator stringConsIterator;

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
		void		handleData(char	buffer[BUFFER_SIZE], int& client);
		std::string	parseClientMessage(std::string message, int& client);

	// Commands
		strings		splitCommands(const std::string& message);
		std::string	helpCommand();
		std::string	capCommand(const strings& commands);
		std::string	joinCommand(const strings& commands, int& client);
		std::string	passCommand(const strings& commands);
		std::string	nickCommand(const strings& commands);
		std::string	userCommand(const strings& commands);
		std::string	modeCommand(const strings& commands);
		std::string	operCommand(const strings& commands);
		std::string	privmsgCommand(const strings& commands);
		std::string	kickCommand(const strings& commands);
		std::string	inviteCommand(const strings& commands);
		std::string	topicCommand(const strings& commands);
		std::string	quitCommand(const strings& commands);
		std::string	partCommand(const strings& commands);
		std::string	pingCommand(const strings& commands);
		std::string	invalidCommand();

	// Util Functions
		std::string			welcomeMsg() const;
		const std::string	currentDateTime();
		void				printMessage(int msg, int index);

	public:
		Server(std::string port, std::string password);
		~Server();
};

#endif
