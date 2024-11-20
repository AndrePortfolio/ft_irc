/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:46:24 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/11/14 13:28:19 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/* Removes ENTER from the command, prepares for parsing and outputs to client */
void	Server::handleData(const char	buffer[BUFFER_SIZE], int& client, struct pollfd(&fds)[MAX_FDS], int& activeFds)
{
	std::string	message(buffer, strlen(buffer));
	if (!message.empty() && (*(message.end() - 1) == '\r' || *(message.end() - 1) == '\n'))
		message.erase(message.end() - 1);

	std::string	outputMsg = parseClientMessage(message, client, fds, activeFds);
	send(clients[client].getSocket(), outputMsg.c_str(), outputMsg.length(), DEFAULT);
}

/* Makes the command case-insensitive */
static std::string toUpper(std::string cmd)
{
	std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
	return (cmd);
}

/* Parses client input, split into commands and execute them */
std::string Server::parseClientMessage(std::string message, int& client, struct pollfd(&fds)[MAX_FDS], int& activeFds)
{

	strings	parameters = splitMessage(message);
	std::string command = toUpper(parameters[0]);

	// General Commands:
	if (command == "CAP")
		return ("");
	if (command == "HELP")
		return (helpCommand());
	else if (command == "OPER")
		return (operCommand(parameters, client));
	else if (command == "PING")
		return (pingCommand(parameters, client));
	else if (command == "QUIT")
		return (quitCommand(parameters, client, fds, activeFds));
	// Login Commands:
	else if (command == "PASS")
		return (passCommand(parameters, client));
	else if (command == "NICK")
		return (nickCommand(parameters, client));
	else if (command == "USER")
		return (userCommand(parameters, client));
	else if (command == "WHOIS")
		return ("");
	// Channel Operations:
	else if (command == "JOIN")
		joinCommand(parameters, client);
	else if (command == "MODE")
		modeCommand(parameters, client);
	else if (command == "TOPIC")
		topicCommand(parameters, client);
	else if (command == "PART")
		partCommand(parameters, client);
	else if (command == "PRIVMSG")
		privmsgCommand(parameters, client);
	else if (command == "INVITE")
		inviteCommand(parameters, client);
	else if (command == "KICK")
		kickCommand(parameters, client);
	else
		return (invalidCommand(message));
	return ("");
}

strings Server::splitMessage(const std::string& message)
{
    strings commands;
    std::istringstream stream(message);
    std::string command;

    if (message.empty()) {
        commands.push_back("Invalid command");
        return commands;
    }
    bool isAllSpaces = true;
    for (size_t i = 0; i < message.size(); ++i)
    {
        if (!isspace(message[i]))
        {
            isAllSpaces = false;
            break;
        }
    }
    if (isAllSpaces)
    {
        commands.push_back("Invalid command");
        return commands;
    }
    while (std::getline(stream, command, ' '))
    {
        if (command.empty() || command[0] == ' ')
        {
            commands.push_back("Invalid command");
            return commands;
        }

        if (command[0] == ':')
        {
            commands.push_back(message.substr(message.find(':')));
            return commands;
        }
        commands.push_back(command);
    }
    return commands;
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
