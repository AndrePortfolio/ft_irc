/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 08:05:46 by apereira          #+#    #+#             */
/*   Updated: 2024/10/18 11:28:37 by apereira         ###   ########.fr       */
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
		std::string	buffer;		// unsure if we need this in this scope
		int			socketFd;
		sockaddr_in	address;
		bool		status;		// unsure if we need this in this scope
		size_t		nb_channels; // # of channels the client is in

	public:
		Client(){Client(0, sockaddr_in());};
		Client(int clientSocket, sockaddr_in clientAddress);
		Client(const Client &copy);
		~Client();
		Client	&operator=(const Client &other);

	// Member Functions
		void				sendMessage(const std::string &command, const std::string &args);
		void				sendMessage(int response_code, const std::string &args);
		void				sendMessage(const std::string &source, const std::string &command, const std::string &args);

	// Accessors
		const size_t		&getNbChannels(void) const;
		void				setNbChannels(size_t nb_channels);
		const std::string	&getNickname(void) const;
		void				setNickname(const std::string &src);
		const std::string	&getUsername(void) const;
		void				setUsername(const std::string &src);
		const std::string	&getRealname(void) const;
		void				setRealname(const std::string &src);
		const std::string	&getBuffer(void) const;
		void				setBuffer(const std::string &src);
		const bool			&getStatus(void) const;
		void				setStatus(const int &status);
		const int			&getSocket(void) const;
		const  sockaddr_in	&getAddress(void) const;

	// Util Functions
		std::string			stringifyCode(int code); // returns the string representation of error codes
		std::string			to_string(int value); // custom implementation due to c++98 std limitations
};

#endif
