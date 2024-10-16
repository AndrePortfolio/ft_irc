/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 08:05:48 by apereira          #+#    #+#             */
/*   Updated: 2024/10/16 11:20:14 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.hpp"

//----------------------------------------------------------------------------//
//--------------------------- Contructors / Destructor -----------------------//
//----------------------------------------------------------------------------//

Client::Client(int clientSocket, sockaddr_in clientAddress)
	:	status(false),
		nickname(),
		username(),
		realname(),
		socketFd(clientSocket),
		address(clientAddress){}

Client::Client(const Client &copy)
{
	*this = copy;
}

Client::~Client()
{
	// if (socketFd >= 0)
	// 	close(socketFd);
}

//----------------------------------------------------------------------------//
//---------------------------------- Operators -------------------------------//
//----------------------------------------------------------------------------//

Client &Client::operator=(Client const &other)
{
	if (this != &other)
	{
		this->nickname = other.nickname;
		this->username = other.username;
		this->realname = other.realname;
		this->status = other.status;
		this->socketFd = other.socketFd;
		this->address = other.address;
	}
	return (*this);
}

//----------------------------------------------------------------------------//
//--------------------------------- Methods ----------------------------------//
//----------------------------------------------------------------------------//

/* -------------------------------- Getters ----------------------------------*/
const std::string	&Client::getNickname(void) const { return (this->nickname); }
const std::string	&Client::getUsername(void) const { return (this->username); }
const std::string	&Client::getRealname(void) const { return (this->realname); }
const bool			&Client::getStatus(void) const { return (this->status); }
const int			&Client::getSocket(void) const { return (this->socketFd); }
const  sockaddr_in	&Client::getAddress(void) const { return (this->address); }

/* -------------------------------- Setters ----------------------------------*/
void	Client::setNickname(const std::string &src) { this->nickname = src; }
void	Client::setUsername(const std::string &src) { this->username = src; }
void	Client::setRealname(const std::string &src) { this->realname = src; }
void	Client::setStatus(const int &status) { this->status = status; }

