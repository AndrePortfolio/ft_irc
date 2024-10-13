/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 08:05:46 by apereira          #+#    #+#             */
/*   Updated: 2024/10/13 13:27:08 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "headers.hpp"

class Client
{
	private:
		bool		status;
		std::string	nickname;
		std::string	username;
		std::string	realname;	// is this requiered?
		std::string	buffer;		// unsure if we need this in this scope
		int			socketFd;
		sockaddr_in	address;

	public:
		Client(){}
		Client(int clientSocket, sockaddr_in clientAddress);
		Client(const Client &copy);
		~Client();
		Client	&operator=(const Client &other);

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
};

#endif
