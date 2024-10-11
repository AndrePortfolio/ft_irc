/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 08:05:46 by apereira          #+#    #+#             */
/*   Updated: 2024/10/11 12:15:39 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "headers.hpp"

class Client
{
	private:
		std::string			nickname;
		std::string			username;
		std::string			realname;
		std::string			buffer;
		bool				status;

		int					socketFd;

		Client(){}

	public:
		Client(int clientSocket);
		Client(Client const &src);
		Client(
			int				socket,
			std::string		nickname,
			std::string		username,
			std::string		realname
			);
		virtual ~Client();

		Client					&operator=(Client const &rhs);

		const std::string		&getNickname(void) const;
		void					setNickname(const std::string &src);
		const std::string		&getUsername(void) const;
		void					setUsername(const std::string &src);
		const std::string		&getRealname(void) const;
		void					setRealname(const std::string &src);
		const std::string		&getBuffer(void) const;
		void					setBuffer(const std::string &src);
		const bool				&getStatus(void) const;
		void					setStatus(const int &status);
		const int				&getSocket(void) const;
};

#endif
