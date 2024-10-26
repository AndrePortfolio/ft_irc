/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:46:24 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/26 11:40:42 by andrealbuqu      ###   ########.fr       */
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

/* Makes the command case-insensitive */
static std::string toUpper(std::string cmd)
{
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
	return (cmd);
}

/* Parses client input, split into commands and execute them */
std::string Server::parseClientMessage(std::string message, int& client)
{
	strings	parameters = splitMessage(message);
	std::string command = toUpper(parameters[0]);

	// General Commands:
	if (command == "CAP")
		return ("");
	if (command == "HELP")
		return (helpCommand());
	else if (command == "OPER")
		return (operCommand(parameters));
	else if (command == "PING")
		return (pingCommand(parameters));
	else if (command == "QUIT")
		return (quitCommand(parameters));
	// Login Commands:
	else if (command == "PASS")
		return (passCommand(parameters, client));
	else if (command == "NICK")
		return (nickCommand(parameters, client));
	else if (command == "USER")
		return (userCommand(parameters, client));
	// Channel Operations:
	else if (command == "JOIN")
		return (joinCommand(parameters, client));
	else if (command == "MODE")
		return (modeCommand(parameters, client));
	else if (command == "TOPIC")
		return (topicCommand(parameters, client));
	else if (command == "PART")
		return (partCommand(parameters, client));
	else if (command == "PRIVMSG")
		return (privmsgCommand(parameters, client));
	else if (command == "INVITE")
		return (inviteCommand(parameters, client));
	else if (command == "KICK")
		return (kickCommand(parameters, client));
	return (invalidCommand(message));
}

/* Spits client message in multiple command arguments, purposly not handling quotes */
strings	Server::splitMessage(const std::string& message)
{
	strings				commands;
	std::istringstream	stream(message);
	std::string			command;

	if (message.empty() || std::all_of(message.begin(), message.end(), isspace))
	{
		commands.push_back("Invalid command");
		return (commands);
	}
	while (std::getline(stream, command, ' '))
	{
		if (command.empty() || command[0] == ' ')
		{
			commands.push_back("Invalid command");
			return (commands);
		}
		if (command[0] == ':')
		{
			commands.push_back(message.substr(message.find(':')));
			return (commands);
		}
		commands.push_back(command);
	}
	return (commands);
}

/* Displays Invalid command message */
std::string	Server::invalidCommand(std::string message)
{
	std::string	msg;

	if (message.empty())
		return (message);
	msg.append(RED);
	msg.append("Invalid command\n");
	msg.append(RESET);
	return (msg);
}
