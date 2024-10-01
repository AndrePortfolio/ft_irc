/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:32:24 by andre-da          #+#    #+#             */
/*   Updated: 2024/10/01 07:29:29 by apereira         ###   ########.fr       */
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
// # include <random>			// For creating random numbers -> COMMENTED BECAUSE IT WON'T COMPILE WITH C++98 standard
# include <ctime>			// For time measurement
#include <ostream>			// For outputting data to streams (e.g., console, file)
#include <cstdlib>			// For general purpose functions like memory management, random number generation, etc.
#include <sys/socket.h>		// For handling socket programming (e.g., socket creation, communication)
#include <netinet/in.h>		// For defining Internet protocol family (e.g., sockaddr_in structure for IPv4)
#include <unistd.h>			// For POSIX operating system API, including system calls like close() and read(

# define RED	"\x1b[31;1m"
# define GREEN	"\x1b[32;1m"
# define BLUE	"\x1b[34;1m"
# define CYAN	"\x1b[36;1m"
# define YELLOW	"\033[33;1m"
# define RESET	"\x1b[0m"

#endif
