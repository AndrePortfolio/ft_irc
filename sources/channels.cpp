/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channels.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 07:53:52 by apereira          #+#    #+#             */
/*   Updated: 2024/11/07 11:23:44 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/channel.hpp"

Channel::Channel()
{
	Channel("", "default_name", NULL);
}

Channel::Channel(std::string mode, std::string name, Client *op)
{
	this->mode = mode;
	this->name = name;
	this->topic = "";
	this->password = "";
	addOperator(op);
	this->usersCount = 0;
}

Channel::Channel(Channel const &src)
{
	*this = src;
}

/*
 ******************************* DESTRUCTOR ***********************************
 */

Channel::~Channel()
{
}

/*
 ******************************** OVERLOAD ************************************
 */

Channel &Channel::operator=(Channel const &src)
{
	if (this != &src)
	{
		this->clients = src.clients;
		this->invited = src.invited;
		this->operators = src.operators;
		this->mode = src.mode;
		this->name = src.name;
		this->key = src.key;
		this->topic = src.topic;
		this->password = src.topic;
		this->usersLimit = src.usersLimit;
		this->usersCount = src.usersCount;
	}
	return (*this);
}

/*
 * Overload the stream insertion operator for Channel to print details about the channel.
 */
std::ostream &Channel::operator<<(std::ostream &o) const
{
	o << "Channel(operators: [";
	for (std::vector<Client*>::const_iterator it = operators.begin(); it != operators.end(); ++it)
	{
		if (it != operators.begin())
			o << ", ";
		o << (*it)->getNickname();
	}
	o << "], name: " << getName()
	  << ", mode: " << getMode() << ")";
	return (o);
}

std::ostream &operator<<(std::ostream &o, const Channel &src)
{
	return (src.operator<<(o));
}

/*
 ******************************** METHODS *************************************
 */

// Add the given client to the channel, map of nick->object
void Channel::addClient(Client *client)
{
	clients[client->getNickname()] = client;
}

// Remove the given client from the channel
void Channel::removeClient(Client *client)
{
	clients.erase(client->getNickname());
}

// Check if the given client is in the channel
bool	Channel::isMember(Client *client)
{
	return (clients.find(client->getNickname()) != clients.end());
}

// Send a message to all clients in the channel
void	Channel::sendMessage(const std::string &source, const std::string &command, const std::string &args)
{
	for (t_nickMapClient::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		it->second->sendMessage(source, command, args);
	}
}

// Send a message to all clients in the channel except the source
void	Channel::privateMessage(const std::string &source, const std::string &command, const std::string &args)
{
	for (t_nickMapClient::iterator it = clients.begin(); it != clients.end(); ++it)
	{
		if (it->second->getNickname() != source)
			it->second->sendMessage(source, command, args);
	}
}

// Check if the channel doesn't have any client
bool    Channel::isEmpty(void)
{
	return (this->getClients().empty());
}

// Return the prefix of the given client in the channel (in this case, only @ for operator)
std::string Channel::getPrefix(Client *client) const
{
	if (isOperator(client))
		return "@";
	return "";
}

// Check if the given client is invited to the channel
bool	Channel::isInvited(Client *client)
{
	return (invited.find(client->getNickname()) != invited.end());
}

// Check if a user is an operator
bool Channel::isOperator(Client* client) const
{
	return (std::find(operators.begin(), operators.end(), client) != operators.end());
}

// Add an operator to the vector
bool Channel::addOperator(Client* client)
{
	if (!isOperator(client))
	{
		operators.push_back(client);
		return (1);
	}
	return (0);
}

bool Channel::removeOperator(Client* client)
{
	std::vector<Client*>::iterator it = std::remove(operators.begin(), operators.end(), client);
	if (it != operators.end())
	{
		operators.erase(it, operators.end());
		return true;
	}
	return false;
}

// Try to add the given mode(s) to the channel and return the effectively added mode(s)
std::string	Channel::addMode(const std::string &real_mode)
{
	std::string ret;

	for (size_t i = 0; i < real_mode.length(); i++)
	{
		if (this->mode.find(real_mode[i]) != std::string::npos)
			continue;
		this->mode += real_mode[i];
		ret += real_mode[i];
	}
	return (ret);
}

// Try to remove the given mode(s) to the channel and return the effectively removed mode(s)
std::string	Channel::delMode(const std::string &real_mode)
{
	std::string ret;
	for (size_t i = 0; i < real_mode.length(); i++)
	{
		if (this->mode.find(real_mode[i]) == std::string::npos)
			continue;
		this->mode.erase(std::remove(this->mode.begin(), this->mode.end(), real_mode[i]), this->mode.end());
		ret += real_mode[i];
	}
	return (ret);
}

// Add the given client to the invited list
void	Channel::addInvited(Client *client)
{
	invited[client->getNickname()] = client;
}

// Remove the given client from the invited list
void	Channel::delInvited(Client *client)
{
	invited.erase(client->getNickname());
}

/*
 ******************************** ACCESSORS ************************************
 */

const	std::string&Channel::getName(void) const { return (this->name); }
void				Channel::setName(const std::string &src) { this->name = src; }

const				Channel::t_nickMapClient &Channel::getClients(void) const { return (this->clients); }
void				Channel::setClients(Channel::t_nickMapClient &src) { this->clients = src; }

const	std::string&Channel::getKey(void) const { return (this->key); }
void				Channel::setKey(std::string &src) { this->key = src; }

const	std::string&Channel::getTopic(void) const { return (this->topic); }
void 				Channel::setTopic(const std::string &src) { this->topic = src; }

int 				Channel::getUserLimit() const { return usersLimit; }
void 				Channel::setUserLimit(int limit){ this->usersLimit = limit; }
void 				Channel::removeUserLimit(){ this->usersLimit = 0; }

int 				Channel::getUserCount() const { return usersCount; }
void 				Channel::setUserCount(int count){ this->usersCount = count; }

void 				Channel::setPassword(const std::string& password) { this->password = password; }
const	std::string&Channel::getPassword() const { return this->password; }
void				Channel::removePassword() { this->password.clear(); }

const Channel::t_nickMapClient &Channel::getInvited(void) const { return (this->invited); }
void Channel::setInvited(t_nickMapClient &src) { this->invited = src; }

const std::string Channel::getMode() const
{
    std::string modeString = "+" + mode; // Start with '+' and add all active mode characters

    if (mode.find('l') != std::string::npos)
    {
        // Convert usersLimit to string using std::stringstream
        std::stringstream ss;
        ss << usersLimit;
        modeString += " " + ss.str(); // Append the user limit if in `+l` mode first
    }

    return modeString;
}

// Returns the symbol of the channel, depending on its mode (s = secret, p = private)
std::string Channel::getSymbol(void) const
{
	if (this->mode.find('s') != std::string::npos)
		return "@";
	else if (this->mode.find('p') != std::string::npos)
		return "*";
	else
		return "=";
}


