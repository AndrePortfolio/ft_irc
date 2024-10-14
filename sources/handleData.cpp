/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:46:24 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/14 10:18:45 by apereira         ###   ########.fr       */
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
	std::cout << "----\nMessage received: " << message << "\n----" << std::endl;

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
		return ("JOIN command\n"); // (to silence irssi), to be changed later
	else if (message == "CAP LS 302")
        return ("CAP * LS :\r\n"); 		// Responds (irssi) indicating no capabilities are supported
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
	else if (message == "PING") // to leave/exit channels
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
	std::string msg;

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
    msg.append("\t   USER <user> * * :<fullname>\n\n");

    msg.append(GREEN);
    msg.append("Available commands:\n");
    msg.append(RESET);
    msg.append(BOLD);
    msg.append("- HELP: Show this help message\n");
    msg.append("- PASS: Set a password for the connection\n");
    msg.append("- NICK <nickname>: Set your nickname\n");
    msg.append("- USER <username>: Register your username\n");
    msg.append("- OPER: Gain operator privileges\n");
    msg.append("- JOIN <channel>: Join a channel\n");
    msg.append("- PRIVMSG <nick/channel> <message>: Send a private message\n");
    msg.append("- KICK <channel> <user>: Kick a user from a channel\n");
    msg.append("- INVITE <nick> <channel>: Invite a user to a channel\n");
    msg.append("- TOPIC <channel> <topic>: Set the channel topic\n");
    msg.append("- MODE <channel/user> <mode>: Change mode of a channel or user\n");
    msg.append("- QUIT: Disconnect from the server\n");
    msg.append("- PING: Ping the server\n");
    msg.append("- PART <channel>: Leave a channel\n");
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
