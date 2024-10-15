/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:46:24 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/15 11:43:43 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/* Removes ENTER from the command, prepares for parsing and outputs to client */
void	Server::handleData(char	buffer[BUFFER_SIZE], int& client)
{
	std::string	message(buffer, strlen(buffer) - 1);
	if (!message.empty() && message.back() == '\r')
		message.erase(message.end() - 1);

	std::string	outputMsg = parseClientMessage(message, client);
	send(clients[client].getSocket(), outputMsg.c_str(), outputMsg.length(), DEFAULT);
}

/* Parses client input */
std::string Server::parseClientMessage(std::string message, int& client)
{
	strings	commands = splitCommands(message);

	// Just for debuging, will delete this
	std::cout << "Commands received: " << commands.size() << "\n----" << std::endl;
	for (stringConsIterator it = commands.begin(); it != commands.end(); ++it)
	{
		std::cout << "Command: " << *it << std::endl;
	}
	return (processCommand(commands, client));
}

/* Spits client message in multiple command arguments */
strings	Server::splitCommands(const std::string& message)
{
	strings				commands;
	std::istringstream	stream(message);
	std::string			command;

	while (std::getline(stream, command, ' '))
		commands.push_back(command);

	return (commands);
}

/* Unsure of what this does, just replicating behavior from previous code */
std::string	Server::capCommand(const strings& commands)
{
	(void)commands;
	// if (commands.size() == 3 && commands[1] == "LS" && commands[2] == "302")
		return ("CAP * LS :\n");
}

/* Unsure of what this does, just replicating behavior from previous code */
std::string	Server::joinCommand(const strings& commands)
{
	(void)commands;
	// if (commands.size() <= 1 || commands[1][0] != '#')
	// 	return (":server 461 * JOIN :No channel specified or invalid channel name\r\n");
	return (":nick!user@server JOIN " "+ channel +" "\r\n:server 332 " "+ channel +" " :Welcome to " "+ channel +" "\r\n");
}

/* Unsure of what this does, just replicating behavior from previous code */
std::string	Server::passCommand(const strings& commands)
{
	(void)commands;
	// if (password.empty())
		// 	return (":server 461 * PASS :Not enough parameters\r\n");
	return (":server 001 * :Password accepted\r\n");
}

/* Unsure of what this does, just replicating behavior from previous code */
std::string	Server::nickCommand(const strings& commands)
{
	(void)commands;
	// if (nickname.empty())
		// 	return (":server 431 * :No nickname given\r\n");
	return (":server 001 " "+ nickname +" " :Welcome, your nickname has been set\r\n");
}

/* Unsure of what this does, just replicating behavior from previous code */
std::string	Server::userCommand(const strings& commands)
{
	(void)commands;
		// if (username.empty())
		// 	return (":server 461 * USER :Not enough parameters\r\n");
	return (":server 001 user :Welcome, you are now registered\r\n");
}

/* Unsure of what this does, just replicating behavior from previous code */
std::string	Server::modeCommand(const strings& commands)
{
	(void)commands;
	// if (target.empty())
		// 	return (":server 461 * MODE :Not enough parameters\r\n");
	return (":server 324 nick +nt\r\n"); // Respond with default mode settings
}

/* Unsure of what this does, just replicating behavior from previous code */
std::string	Server::partCommand(const strings& commands)
{
	(void)commands;
	// if (channel.empty())
		// 	return (":server 461 * PART :No channel specified\r\n");
	return (":server 331 nick :Left channel " "+ channel +" "\r\n");
}

/* Unsure of what this does, just replicating behavior from previous code */
std::string	Server::operCommand(const strings& commands)
{
	(void)commands;
	return ("");
}

/* Unsure of what this does, just replicating behavior from previous code */
std::string	Server::privmsgCommand(const strings& commands)
{
	(void)commands;
	return ("");
}

/* Unsure of what this does, just replicating behavior from previous code */
std::string	Server::kickCommand(const strings& commands)
{
	(void)commands;
	return ("");
}

/* Unsure of what this does, just replicating behavior from previous code */
std::string	Server::inviteCommand(const strings& commands)
{
	(void)commands;
	return ("");
}

/* Unsure of what this does, just replicating behavior from previous code */
std::string	Server::topicCommand(const strings& commands)
{
	(void)commands;
	return ("");
}

/* Unsure of what this does, just replicating behavior from previous code */
std::string	Server::quitCommand(const strings& commands)
{
	(void)commands;
	return ("");
}

/* Unsure of what this does, just replicating behavior from previous code */
std::string	Server::pingCommand(const strings& commands)
{
	(void)commands;
	return ("");
}

/* Processes individual command */
std::string Server::processCommand(const strings& commands, int& client)
{
	(void)client;
	if (commands[0] == "HELP")
		return (helpCommand());
	else if (commands[0] == "CAP")
		return (capCommand(commands));
	else if (commands[0] == "JOIN")
		return (joinCommand(commands));
	else if (commands[0] == "PASS")
		return (passCommand(commands));
	else if (commands[0] == "NICK")
		return (nickCommand(commands));
	else if (commands[0] == "USER")
		return (userCommand(commands));
	else if (commands[0] == "MODE")
		return (modeCommand(commands));
	else if (commands[0] == "OPER")
		return (operCommand(commands));
	else if (commands[0] == "PRIVMSG")
		return (privmsgCommand(commands));
	else if (commands[0] == "KICK")
		return (kickCommand(commands));
	else if (commands[0] == "INVITE")
		return (inviteCommand(commands));
	else if (commands[0] == "TOPIC")
		return (topicCommand(commands));
	else if (commands[0] == "QUIT")
		return (quitCommand(commands));
	else if (commands[0] == "PART")
		return (partCommand(commands));
	else if (commands[0] == "PING")
		return (pingCommand(commands));
	return (invalidCommand());
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
