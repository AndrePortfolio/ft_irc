/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 08:05:48 by apereira          #+#    #+#             */
/*   Updated: 2024/10/11 12:32:14 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.hpp"

Client::Client(int clientSocket)
	:	nickname(),
		username(),
		realname(),
		buffer(),
		status(false),
		socketFd(clientSocket){}

Client::Client(const Client &copy)
{
	*this = copy;
}

Client::~Client()
{
	// if (socketFd >= 0)
	// 	close(socketFd);
}

Client &Client::operator=(Client const &other)
{
	if (this != &other)
	{
		this->nickname = other.nickname;
		this->username = other.username;
		this->realname = other.realname;
		this->buffer = other.buffer;
		this->status = other.status;
		this->socketFd = other.socketFd;
	}
	return (*this);
}

const std::string &Client::getNickname(void) const
{
	return (this->nickname);
}

void Client::setNickname(const std::string &src)
{
	this->nickname = src;
}

const std::string &Client::getUsername(void) const
{
	return (this->username);
}

void Client::setUsername(const std::string &src)
{
	this->username = src;
}

const std::string &Client::getRealname(void) const
{
	return (this->realname);
}

void	Client::setRealname(const std::string &src)
{
	this->realname = src;
}

const std::string &Client::getBuffer(void) const
{
	return (this->buffer);
}

void	Client::setBuffer(const std::string &src)
{
	this->buffer = src;
}

const	bool	&Client::getStatus(void) const
{
	return (this->status);
}

void	Client::setStatus(const int &status)
{
	this->status = status;
}

const int	&Client::getSocket(void) const
{
	return (this->socketFd);
}
