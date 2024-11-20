/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:15:56 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/11/20 09:41:09 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "headers.hpp"

class Client;
class Channel;

typedef std::map<int, Client> Clients;
typedef std::map<int, Client>::iterator clientsIterator;
typedef std::vector<std::string> strings;
typedef std::vector<std::string>::const_iterator stringConsIterator;
typedef std::map<std::string, Channel *>	t_nameMapChannel;	// map of channel name to channel object
typedef t_nameMapChannel::iterator			t_channelIterator;	// iterator for the map
typedef std::vector<std::pair<std::string, std::string> > Operators;
typedef std::vector<std::pair<std::string, std::string> >::iterator	opIterator;

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
		void		updatePool(pollfd& fds, int& activeFds, int socket);
		void		checkForEvent(pollfd(&fds)[MAX_FDS], int& activeFds);
		void		listenForClients(pollfd(&fds)[MAX_FDS], int& activeFds);
		void		CheckForClientData(pollfd(&fds)[MAX_FDS], int& activeFds);
		void		receivedNewData(pollfd(&fds)[MAX_FDS], int& client, int& activeFds);
		void		adjustClients(pollfd(&fds)[MAX_FDS], int i, int& activeFds);
		void		handleData(const char	buffer[BUFFER_SIZE], int& client, pollfd(&fds)[MAX_FDS], int& activeFds);
		std::string	parseClientMessage(std::string message, int& client, pollfd(&fds)[MAX_FDS], int& activeFds);
		void		parseData(pollfd(&fds)[MAX_FDS], char	buffer[BUFFER_SIZE], int client, int bytesRead, int& activeFds);

	// Commands
		strings		splitMessage(const std::string& message);
		std::string	helpCommand();
		std::string	passCommand(const strings& parameters, int& client);
		std::string	nickCommand(const strings& parameters, int& client);
		std::string	userCommand(const strings& parameters, int& client);
		std::string	operCommand(const strings& parameters, int& client);
		std::string	quitCommand(const strings& parameters, int& client, pollfd(&fds)[MAX_FDS], int& activeFds);
		std::string	pingCommand(const strings& parameters, int& client);
		void		inviteCommand(const strings& commands, int& cindex);
		void		joinCommand(const strings& parameters, int& cindex);
		void		kickCommand(std::vector<std::string> tokens, int& cindex);
		void		partCommand(const strings& parameters, int& cindex);
		void		privmsgCommand(const strings& parameters, int& cindex);
		void		topicCommand(const strings& parameters, int& cindex);
		std::string	invalidCommand(std::string message);

	// Mode command and aux's
		void		modeCommand(const strings& commands, int& cindex);
		int			ignoreInitialMsg(const std::string command);
		void		handleChannelMode(const strings& commands, int& cindex);
		void		validateModeCharacters(const strings& commands, int& cindex);
		void		updateChannelMode(const strings& commands, int& cindex, Channel* channel);
		void		handleInviteOnlyMode(bool addMode, Channel* channel, std::string& buffer_add, std::string& buffer_del);
		void		handleTopicMode(bool addMode, Channel* channel, std::string& buffer_add, std::string& buffer_del);
		void		handleOperatorMode(bool addMode, const strings& commands, int& cindex, Channel* channel, size_t& argIndex, std::string& buffer_add, std::string& buffer_del);
		void		handleLimitMode(bool addMode, const strings& commands, int& cindex, Channel* channel, size_t& argIndex, std::string& buffer_add, std::string& buffer_del);
		void		handleUserMode(const strings& commands, int& cindex);
		void		handlePasswordMode(bool addMode, const strings& commands, int& cindex, Channel* channel, size_t& argIndex, std::string& buffer_add, std::string& buffer_del);
		void		parseChannelNamesAndPasswords(const std::string& input, std::vector<std::string>& channel_names, std::vector<std::string>& passwords);

	// Channels
		bool		existsChannel(std::string name) const;
		void		deleteChannel(const std::string& channelName);
		bool 		existsClient(const std::string& name) const;
		char  		closestPlusMinus(const std::string &str, const char &mode) const;
		int			findClientIndexByNickname(const std::string& nickname) const;
		void		handleLeaveAllChannels(const strings& commands, int &cindex);
		void		processChannelNames(const std::vector<std::string>& channel_names, int &cindex);
		bool		isValidChannelName(const std::string& channelName);
		void		handleExistingOrNewChannel(const std::string& channelName, const std::string& channelPassword, int &cindex, std::vector<Channel *> &channels_to_sub);
		void		createNewChannel(const std::string& channelName, const std::string& channelPassword, int &cindex, std::vector<Channel *> &channels_to_sub);
		void		joinChannels(std::vector<Channel *> &channels_to_sub, int &cindex);

	// Utility Functions
		std::string					welcomeMsg() const;
		const std::string			currentDateTime();
		void						printMessage(int msg, int index);
		std::vector<std::string>	split(std::string str, char c) const;
		const t_nameMapChannel&		getChannels(void) const { return (channels); };
		t_nameMapChannel&			getChannels(void) { return (channels); };
		void 						setChannels(const t_nameMapChannel &src) { channels = src; };
		std::string					feedbackClient(int input);
		void						feedbackClients(int client, int clientID, std::string reason, Channel* channel);
		const std::string			getMessage(int input, int index);
		void						informOtherClients(int index, std::string nickname);
		bool						invalidChars(std::string nick);

	public:
		Server(std::string port, std::string password);
		~Server();
};

#endif
