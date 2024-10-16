/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:32:24 by andre-da          #+#    #+#             */
/*   Updated: 2024/10/16 14:14:12 by andrealbuqu      ###   ########.fr       */
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

// Print Message
# define SERVER 0
# define LISTENING 1
# define NEW_CONNECTION 2
# define DISCONNECTED 3

// Feedback Client
# define ERR_NEEDMOREPARAMS 461
# define ERR_ALREADYREGISTERED 462
# define ERR_NOTAUTHENTICATED 463
# define ERR_INVALIDPASSWORD 464
# define ERR_NONICKNAMEGIVEN 431
# define ERR_ERRONEUSNICKNAME 432
# define ERR_NICKNAMEINUSE 433
# define ERR_NICKCOLLISION 436

# define RED	"\x1b[31;1m"
# define GREEN	"\x1b[32;1m"
# define BLUE	"\x1b[34;1m"
# define CYAN	"\x1b[36;1m"
# define YELLOW	"\033[33;1m"
# define BOLD	"\033[1m"
# define RESET	"\x1b[0m"

# include "server.hpp"
# include "client.hpp"

#endif
