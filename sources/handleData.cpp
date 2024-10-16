/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:46:24 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/16 10:42:27 by andrealbuqu      ###   ########.fr       */
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

/* Parses client input, split into commands and execute them */
std::string Server::parseClientMessage(std::string message, int& client)
{
	strings	commands = splitCommands(message);

	// General Commands:
	if (commands[0] == "HELP")
		return (helpCommand());
	else if (commands[0] == "OPER")
		return (operCommand(commands));
	else if (commands[0] == "PING")
		return (pingCommand(commands));
	else if (commands[0] == "QUIT")
		return (quitCommand(commands));
	// Login Commands:
	else if (commands[0] == "PASS")
		return (passCommand(commands));
	else if (commands[0] == "NICK")
		return (nickCommand(commands));
	else if (commands[0] == "USER")
		return (userCommand(commands));
	// Channel Operations:
	else if (commands[0] == "JOIN")
		return (joinCommand(commands, client));
	else if (commands[0] == "MODE")
		return (modeCommand(commands, client));
	else if (commands[0] == "TOPIC")
		return (topicCommand(commands, client));
	else if (commands[0] == "PART")
		return (partCommand(commands, client));
	else if (commands[0] == "PRIVMSG")
		return (privmsgCommand(commands, client));
	else if (commands[0] == "INVITE")
		return (inviteCommand(commands, client));
	else if (commands[0] == "KICK")
		return (kickCommand(commands, client));
	return (invalidCommand());
}

/* Spits client message in multiple command arguments */
strings	Server::splitCommands(const std::string& message)
{
	strings				commands;
	std::istringstream	stream(message);
	std::string			command;

	while (std::getline(stream, command, ' '))
	{
		if (command.empty() || command[0] == ' ')
		{
			commands.push_back("Invalid command");
			return (commands);
		}
		if (command[0] == ':')
		{
			commands.push_back(message.substr(message.find(':') + 1));
			return (commands);
		}
		commands.push_back(command);
	}
	return (commands);
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
