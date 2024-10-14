/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:46:24 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/14 14:51:38 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/* Removes ENTER from the command, prepares for parsing and outputs to client */
void	Server::handleData(char	buffer[BUFFER_SIZE], int& client)
{
	std::string	message(buffer, strlen(buffer) - 1);
	if (message.back() == '\r')
		message.erase(message.end() - 1);

	std::string	outputMsg = parseClientMessage(message, client);
	feebackClient(outputMsg, client);
}

/* Parses client input */
std::string Server::parseClientMessage(std::string message, int& client)
{
	(void)client;	// delete once used;

	if (message == "HELP")
		return (helpCommand());
	else if (message == "PASS")
	{}
	else if (message == "NICK")
	{}
	else if (message == "USER")
	{}
	else if (message == "OPER")
	{}
	else if (message == "JOIN")
	{}
	else if (message == "PRIVMSG")
	{}
	else if (message == "KICK")
	{}
	else if (message == "INVITE")
	{}
	else if (message == "TOPIC")
	{}
	else if (message == "MODE")
	{}
	else if (message == "QUIT")
	{}
	else if (message == "PART")
	{}
	else if (message == "PING")
	{}
	// else
	return (invalidCommand());
}

/* Sends feedback to client */
void	Server::feebackClient(std::string outputMsg, int& client)
{
	outputMsg.append("\n");
	send(clients[client].getSocket(), outputMsg.c_str(), outputMsg.length(), DEFAULT);
}

/* Displays how to Login */
std::string	Server::helpCommand()
{
	std::string	msg;

	msg.append(GREEN);
	msg.append("STEP 1 -> ");
	msg.append(RESET);
	msg.append("Set a password:\n");
	msg.append(BOLD);
	msg.append("\t   PASS <Password>\n\n");
	msg.append(GREEN);
	msg.append("STEP 2 -> ");
	msg.append(RESET);
	msg.append("Set a nickname:\n");
	msg.append(BOLD);
	msg.append("\t   NICK <nick>\n\n");
	msg.append(GREEN);
	msg.append("STEP 3 -> ");
	msg.append(RESET);
	msg.append("Set a username and fullname:\n");
	msg.append(BOLD);
	msg.append("\t   USER <user> * * :<fullname>\n");
	msg.append(RESET);
	return (msg);
}

/* Displays Invalid command message */
std::string	Server::invalidCommand()
{
	std::string	msg;

	msg.append(RED);
	msg.append("Invalid command\n");
	msg.append(RESET);
	return (msg);
}
