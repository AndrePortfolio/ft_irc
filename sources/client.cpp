/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 08:05:48 by apereira          #+#    #+#             */
/*   Updated: 2024/10/31 09:27:07 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/client.hpp"

//----------------------------------------------------------------------------//
//--------------------------- Contructors / Destructor -----------------------//
//----------------------------------------------------------------------------//

Client::Client(int clientSocket, sockaddr_in clientAddress)
	:	nickname(),
		username(),
		realname(),
		socketFd(clientSocket),
		status(false),
		mode(),
		nb_channels(),
		address(clientAddress),
		password(),
		serverOperator(false)
{
	this->buffer = "";
	this->nb_channels = 0;
}

Client::Client()
	:	nickname(),
		username(),
		realname(),
		buffer(),
		socketFd(-1),
		status(false),
		mode(),
		nb_channels(),
		address(),
		password(),
		serverOperator(false){}

Client::Client(const Client &copy)
{
	*this = copy;
}

Client::~Client(){}

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
		this->nb_channels = other.nb_channels;
		this->password = other.password;
		this->serverOperator = other.serverOperator;
	}
	return (*this);
}

//----------------------------------------------------------------------------//
//--------------------------------- Methods ----------------------------------//
//----------------------------------------------------------------------------//

// Stringify the given response code to a 3-digit string (%03d)
std::string	Client::stringifyCode(int code)
{
	std::string		str = to_string(code);

	while (str.length() < 3)
		str = "0" + str;
	return (str);
}

// Custom function to convert an integer to string, similar to std::to_string
std::string Client::to_string(int value)
{
    std::stringstream ss;
    ss << value;
    return (ss.str());
}

// Send a message to the client with the given response code
void Client::sendMessage(int response_code, const std::string &args)
{
	sendMessage(stringifyCode(response_code), args);
}

// Send a message to the client
void Client::sendMessage(const std::string &command, const std::string &args)
{
	sendMessage("ft_irc", command, args);
}

// Send a message to the client with the given response code and the given source
void Client::sendMessage(const std::string &source, const std::string &command, const std::string &args)
{
	std::string	editable(command);
	editable = ":" + source + " " + editable;
	editable += " ";
	editable += args;
	editable += "\r\n";
	send(this->socketFd, editable.c_str(), editable.length(), 0);
}


void	Client::addMode(const std::string &mode)
{
	for (size_t i = 0; i < mode.length(); i++)
	{
		if (std::find(this->mode.begin(), this->mode.end(), mode[0]) == this->mode.end())
			continue;
		this->mode += mode[i];
	}
}

void	Client::delMode(const std::string &mode)
{
	for (size_t i = 0; i < mode.length(); i++)
	{
		if (find(this->mode.begin(), this->mode.end(), mode[0]) != this->mode.end())
			continue;
		this->mode.erase(std::remove(this->mode.begin(), this->mode.end(), mode[i]), this->mode.end());
	}
}
/* -------------------------------- Getters ----------------------------------*/
const std::string	&Client::getNickname(void) const { return (this->nickname); }
const std::string	&Client::getUsername(void) const { return (this->username); }
const std::string	&Client::getRealname(void) const { return (this->realname); }
const bool			&Client::getStatus(void) const { return (this->status); }
const bool			&Client::getOperator(void) const { return (this->serverOperator); }
const int			&Client::getSocket(void) const { return (this->socketFd); }
const size_t 		&Client::getNbChannels(void) const { return this->nb_channels; }
const std::string	&Client::getMode(void) const { return this->mode; }
const sockaddr_in	&Client::getAddress(void) const { return (this->address); }
const std::string	&Client::getPassword(void) const { return (this->password); }

/* -------------------------------- Setters ----------------------------------*/
void	Client::setNickname(const std::string &src) { this->nickname = src; }
void	Client::setUsername(const std::string &src) { this->username = src; }
void	Client::setRealname(const std::string &src) { this->realname = src; }
void	Client::setBuffer(const std::string &src) { this->buffer = src; }
void 	Client::setNbChannels(size_t nb_channels) { this->nb_channels = nb_channels; }
void	Client::setStatus(const bool &status) { this->status = status; }
void	Client::setOperator(const bool &status) { this->serverOperator = status; }
void	Client::setPassword(const std::string  &password) { this->password = password; }

