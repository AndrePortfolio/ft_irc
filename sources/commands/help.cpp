/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:38 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/15 10:06:46 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

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
