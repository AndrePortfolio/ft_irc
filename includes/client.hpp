/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 08:05:46 by apereira          #+#    #+#             */
/*   Updated: 2024/11/04 13:33:21 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "headers.hpp"

class Client
{
	private:
		std::string	nickname;
		std::string	username;
		std::string	realname;
		std::string	buffer;
		int			socketFd;
		bool		status;
		std::string	mode;
		size_t		nb_channels; // # of channels the client is in
		sockaddr_in	address;
		std::string	password;
		bool		serverOperator;

	public:
		Client();
		Client(int clientSocket, sockaddr_in clientAddress);
		Client(const Client &copy);
		~Client();
		Client	&operator=(const Client &other);

	// Member Functions
		void				sendMessage(const std::string &command, const std::string &args);
		void				sendMessage(int response_code, const std::string &args);
		void				sendMessage(const std::string &source, const std::string &command, const std::string &args);
		void				addMode(const std::string &mode);
		void				delMode(const std::string &mode);

	// Accessors
		const size_t		&getNbChannels(void) const;
		void				setNbChannels(size_t nb_channels);
		const std::string	&getNickname(void) const;
		void				setNickname(const std::string &src);
		const std::string	&getUsername(void) const;
		void				setUsername(const std::string &src);
		const std::string	&getRealname(void) const;
		void				setRealname(const std::string &src);
		const bool			&getStatus(void) const;
		void				setStatus(const bool &status);
		const int			&getSocket(void) const;
		const  sockaddr_in	&getAddress(void) const;
		const std::string	&getMode(void) const;
		void				setBuffer(const std::string &src);

	// Util Functions
		std::string			stringifyCode(int code); // returns the string representation of error codes
		std::string			to_string(int value); // custom implementation due to c++98 std limitations
		void				setPassword(const std::string &password);
		const std::string	&getPassword(void) const;
		const bool			&getOperator(void) const;
		void				setOperator(const bool &status);
};

#endif
