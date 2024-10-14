/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleData.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:46:24 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/14 13:16:40 by apereira         ###   ########.fr       */
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

std::vector<std::string> Server::splitCommands(const std::string& message)
{
    std::vector<std::string> commands;
    std::istringstream stream(message);
    std::string command;

    while (std::getline(stream, command, '\n'))
    {
        if (!command.empty() && command.back() == '\r')
        {
            command.pop_back(); // Remove trailing carriage return
        }
        commands.push_back(command);
    }

    return (commands);
}

/* Processes individual command */
std::string Server::processCommand(const std::string& command)
{
    std::istringstream commandStream(command);
    std::string cmd;
    commandStream >> cmd;
	
    if (cmd == "HELP")
        return (helpCommand());
    else if (cmd == "CAP" && command.find("LS 302") != std::string::npos)
        return ("CAP * LS :\r\n"); // Respond indicating no capabilities are supported
     else if (cmd == "JOIN")
    {
        std::string channel;
        commandStream >> channel;
        if (channel.empty() || channel[0] != '#')
            return (":server 461 * JOIN :No channel specified or invalid channel name\r\n");
        // return (":nick!user@server JOIN " + channel + "\r\n:server 332 " + channel + " :Welcome to " + channel + "\r\n");
    }
    else if (cmd == "PASS")
    {
        std::string password;
        commandStream >> password;
        if (password.empty())
            return (":server 461 * PASS :Not enough parameters\r\n");
        // return (":server 001 * :Password accepted\r\n");
    }
    else if (cmd == "NICK")
    {
        std::string nickname;
        commandStream >> nickname;
        if (nickname.empty())
            return (":server 431 * :No nickname given\r\n");
        // return (":server 001 " + nickname + " :Welcome, your nickname has been set\r\n");
    }
    else if (cmd == "USER")
    {
        std::string username;
        commandStream >> username;
        if (username.empty())
            return (":server 461 * USER :Not enough parameters\r\n");
        // return (":server 001 user :Welcome, you are now registered\r\n");
    }
    else if (cmd == "MODE")
    {
        std::string target;
        commandStream >> target;
        if (target.empty())
            return (":server 461 * MODE :Not enough parameters\r\n");
        return (":server 324 nick +nt\r\n"); // Respond with default mode settings
    }
    else if (cmd == "OPER")
        return ("OPER command\n");
    else if (cmd == "PRIVMSG")
        return ("PRIVMSG command\n");
    else if (cmd == "KICK")
        return ("KICK command\n");
    else if (cmd == "INVITE")
        return ("INVITE command\n");
    else if (cmd == "TOPIC")
        return ("TOPIC command\n");
    else if (cmd == "QUIT")
        return ("QUIT command\n");
    else if (cmd == "PART")
    {
        std::string channel;
        commandStream >> channel;
        if (channel.empty())
            return (":server 461 * PART :No channel specified\r\n");
        return (":server 331 nick :Left channel " + channel + "\r\n");
    }
    else if (cmd == "PING")
        return ("PONG :server\r\n"); // Respond to PING with PONG
    else
        return (invalidCommand());
}

/* Parses client input */
std::string Server::parseClientMessage(std::string message, int& client)
{
    (void)client; // delete once used;
	
    std::cout << "----\nMessage received: " << message << "\n--------" << std::endl;

    std::vector<std::string> commands = splitCommands(message);
	
	std::cout << "Commands received: " << commands.size() << "\n----" << std::endl;
	for (std::vector<std::string>::const_iterator it = commands.begin(); it != commands.end(); ++it)
	{
		std::cout << "Command: " << *it << std::endl;
	}

    for (std::vector<std::string>::const_iterator it = commands.begin(); it != commands.end(); ++it)
    {
        std::string response = processCommand(*it);
        feebackClient(response, client);
    }

    return ""; // No need to return a concatenated response
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
