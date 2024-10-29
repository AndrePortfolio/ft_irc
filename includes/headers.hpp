/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:32:24 by andre-da          #+#    #+#             */
/*   Updated: 2024/10/29 09:38:47 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADERS_HPP
# define HEADERS_HPP

# include <iostream>		// For input and output stream
# include <string>			// For string class and functions
# include <cstring>			// For C-style string functions
# include <cmath>			// For common mathematical functions
# include <sstream>			// For string stream classes
# include <fstream>			// For file stream classes
# include <iomanip>			// For input/output manipulation
# include <exception>		// For standard exception classes
# include <stdexcept>		// For standard exception classes (runtime_error, etc.)
# include <limits>			// For numeric limits
# include <typeinfo>		// For type information
# include <vector>			// For using the vector container
# include <list>	 		// For using the list container
# include <map>		 		// For using the map container
# include <algorithm>		// For using algorithms like sort, find, etc.
# include <deque>	 		// For deque
# include <stack>	 		// For stack
# include <ctime>			// For time measurement
# include <ostream>			// For outputting data to streams (e.g., console, file)
# include <cstdlib>			// For general purpose functions like memory management, random number generation, etc.
# include <sys/socket.h>	// For handling socket programming (e.g., socket creation, communication)
# include <sys/types.h> 	// For socket()
# include <netinet/in.h> 	// For sockaddr_in
# include <fcntl.h> 		// For fcntl()
# include <unistd.h> 		// For close()
# include <arpa/inet.h> 	// For inet_ntoa()
# include <poll.h> 			// For poll()
# include <csignal> 		// For signal()

# define BUFFER_SIZE 1024
# define MAX_FDS 1024
# define MAX_CONNECTIONS 5
# define WAIT_INDEFINITELY -1
# define DEFAULT 0
# define CLIENT_DISCONNECTED 0
# define ERROR -1
# define MIN_ALLOWED_PORT 1024
# define MAX_ALLOWED_PORT 65535
# define DEFAULT_FDS 4

# define SERVER 0
# define NEW_CONNECTION 2
# define DISCONNECTED 3
# define LISTENING 1

enum numeric_rpl
{
	RPL_WELCOME = 001,
	RPL_YOURHOST = 002,
	RPL_CREATED = 003,
	RPL_MYINFO = 004,
	RPL_ISUPPORT = 005,
	RPL_UMODEIS = 221,
	RPL_CHANNELMODEIS = 324,
	RPL_NOTOPIC = 331,
	RPL_TOPIC = 332,
	RPL_INVITING = 341,
	RPL_NAMREPLY = 353,
	RPL_ENDOFNAMES = 366,
	RPL_MOTD = 372,
	RPL_MOTDSTART = 375,
	RPL_ENDOFMOTD = 376,
};

enum numeric_err
{
	ERR_NOSUCHNICK = 401,
	ERR_NOSUCHSERVER = 402,
	ERR_NOSUCHCHANNEL = 403,
	ERR_TOOMANYCHANNELS = 405,
	ERR_UNKNOWNCOMMAND = 421,
	ERR_NOMOTD = 422,
	ERR_NONICKNAMEGIVEN = 431,
	ERR_ERRONEUSNICKNAME = 432,
	ERR_NICKNAMEINUSE = 433,
	ERR_USERNOTINCHANNEL = 441,
	ERR_NOTONCHANNEL = 442,
	ERR_USERONCHANNEL = 443,
	ERR_NOTREGISTERED = 451,
	ERR_NEEDMOREPARAMS = 461,
	ERR_ALREADYREGISTERED = 462,
	ERR_PASSWDMISMATCH = 464,
	ERR_CHANNELISFULL = 471,
	ERR_UNKNOWNMODE = 472,
	ERR_INVITEONLYCHAN = 473,
	ERR_BADCHANNELKEY = 475,
	ERR_BADCHANMASK = 476,
	ERR_CHANOPRIVSNEEDED = 482,
	ERR_USERSDONTMATCH = 502,
};

# define RED	"\x1b[31;1m"
# define GREEN	"\x1b[32;1m"
# define BLUE	"\x1b[34;1m"
# define CYAN	"\x1b[36;1m"
# define YELLOW	"\033[33;1m"
# define BOLD	"\033[1m"
# define RESET	"\x1b[0m"

# include "channel.hpp"
# include "server.hpp"
# include "client.hpp"

#endif
