/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 08:05:48 by apereira          #+#    #+#             */
/*   Updated: 2024/10/02 08:22:24 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.hpp"

Client::Client()
{
	Client(-1, "", "", "");
}

Client::Client(int socket, std::string nickname, std::string username, std::string realname)
{
	this->nickname = nickname;
	this->username = username;
	this->realname = realname;
	this->buffer = "";
	this->connection_status = 0;
}

Client::Client(Client const &src)
{
	*this = src;
}

Client::~Client()
{
	
}

Client &Client::operator=(Client const &src)
{
	if (this != &src)
	{
		this->nickname = src.nickname;
		this->username = src.username;
		this->realname = src.realname;
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

const	int	&Client::getConnectionStatus(void) const
{
	return (this->connection_status);
}

void	Client::setConnectionStatus(const int &status)
{
	this->connection_status = status;
}

