/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:32:24 by andre-da          #+#    #+#             */
/*   Updated: 2024/10/18 10:53:46 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "headers.hpp"

class Client;
class Channel;

typedef std::map<int, Client> Clients;
typedef std::vector<std::string> strings;
typedef std::vector<std::string>::const_iterator stringConsIterator;
typedef std::map<std::string, Channel *>	t_nameMapChannel;	// map of channel name to channel object
typedef t_nameMapChannel::iterator			t_channelIterator;	// iterator for the map

class Server
{
	private:
		int					port;
		std::string			password;
		bool				signal;
		int					socketFd;
		sockaddr_in			address;
		Clients				clients;
		t_nameMapChannel	channels;
		std::string			chanmodes;
		std::string			chantypes;
		size_t				chanlimit;
		size_t				channellen;
		size_t				modes;
		size_t				topiclen;

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
		void		parseClientMessage(std::string message, int& client);

	// Commands
		strings		splitCommands(const std::string& message);
		std::string	helpCommand();
		std::string	capCommand(const strings& commands);

		std::string	passCommand(const strings& commands);
		std::string	nickCommand(const strings& commands);
		std::string	userCommand(const strings& commands);
		void		joinCommand(const strings& commands, int& client);
		void		modeCommand(const strings& commands, int& client);
		void		topicCommand(const strings& commands, int& client);
		void		partCommand(const strings& commands, int& client);
		void		privmsgCommand(const strings& commands, int& client);
		void		inviteCommand(const strings& commands, int& client);
		void		kickCommand(const strings& commands, int& client);
		std::string	operCommand(const strings& commands);
		std::string	quitCommand(const strings& commands);
		std::string	pingCommand(const strings& commands);
		std::string	invalidCommand();

	//Channels
		bool			existsChannel(std::string name) const;
		void			removeChannel(std::string channel_name);

	// Util Functions
		std::string					welcomeMsg() const;
		const std::string			currentDateTime();
		void						printMessage(int msg, int index);
		std::vector<std::string>	split(std::string str, char c) const;
		const t_nameMapChannel&		getChannels(void) const { return (channels); };
		t_nameMapChannel&			getChannels(void) { return (channels); };
		void 						setChannels(const t_nameMapChannel &src) { channels = src; };



	public:
		Server(std::string port, std::string password);
		~Server();
};

#endif
