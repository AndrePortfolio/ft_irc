/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 08:05:46 by apereira          #+#    #+#             */
/*   Updated: 2024/10/02 08:22:50 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_CLASS_HPP
#define CLIENT_CLASS_HPP

#include "headers.hpp"

class Client
{
private:
	std::string			nickname;
	std::string			username;
	std::string			realname;
	std::string			buffer;
	int					connection_status;	

public:
	Client();
	Client(Client const &src);
	Client(
		int				fd,
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
	const int				&getConnectionStatus(void) const;
	void					setConnectionStatus(const int &status);
};

#endif