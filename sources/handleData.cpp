/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:46:24 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/16 11:17:00 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/* Removes ENTER from the command, prepares for parsing and outputs to client */
void	Server::handleData(char	buffer[BUFFER_SIZE], int& client)
{
	std::string	message(buffer, strlen(buffer) - 1);
	if (!message.empty() && *(message.end() - 1) == '\r')
		message.erase(message.end() - 1);

	// std::string	outputMsg = ---> check message below
	parseClientMessage(message, client);
	// send(clients[client].getSocket(), outputMsg.c_str(), outputMsg.length(), DEFAULT); ---> implemented send_message into client
	// and server class to avoid spaghetti code
}

/* Just for debuging, will delete this */
static void	debugCommandSplit(strings commands)
{
	std::cout << "Commands received: " << commands.size() << "\n----" << std::endl;
	for (stringConsIterator it = commands.begin(); it != commands.end(); ++it)
		std::cout << "Command: " << *it << std::endl;
}

/* Parses client input, split into commands and execute them */
void Server::parseClientMessage(std::string message, int& client)
{
	strings	commands = splitCommands(message);

	debugCommandSplit(commands); // Just for debuging, will delete this

	// General Commands:
	// if (commands[0] == "HELP")
	// 	helpCommand();
	// else if (commands[0] == "CAP")
	// 	capCommand(commands);
	// // Login Commands:
	// else if (commands[0] == "PASS")
	// 	passCommand(commands);
	// else if (commands[0] == "NICK")
	// 	return (nickCommand(commands));
	// else if (commands[0] == "USER")
	// 	return (userCommand(commands));
	// Channel Operations:
	if (commands[0] == "JOIN")
		joinCommand(commands, client);
	else if (commands[0] == "MODE")
		modeCommand(commands, client);
	else if (commands[0] == "TOPIC")
		topicCommand(commands, client);
	else if (commands[0] == "PART")
		partCommand(commands, client);
	else if (commands[0] == "PRIVMSG")
		privmsgCommand(commands, client);
	else if (commands[0] == "INVITE")
		inviteCommand(commands, client);
	else if (commands[0] == "KICK")
		kickCommand(commands, client);
	// // Server Adminstration and Maintenance:
	// else if (commands[0] == "OPER")
	// 	return (operCommand(commands));
	// else if (commands[0] == "PING")
	// 	return (pingCommand(commands));
	// else if (commands[0] == "QUIT")
	// 	return (quitCommand(commands));
	else
		invalidCommand();
}

/* Splits client message in multiple command arguments */
strings	Server::splitCommands(const std::string& message)
{
	strings				commands;
	std::istringstream	stream(message);
	std::string			command;

	// still need to protect for double space and space in the beginning
	// still need to protect for no space before :
	while (std::getline(stream, command, ' '))
	{
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
