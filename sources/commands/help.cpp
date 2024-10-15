/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:38 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/15 10:46:38 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/* Displays how to Login */
std::string	Server::helpCommand()
{
	std::string msg;

	msg.append(BOLD);
	msg.append("\nLogin Instructions:\n");
	msg.append(GREEN);
	msg.append("STEP 1 -> ");
	msg.append(RESET);
	msg.append("Set a password:\n");
	msg.append(BOLD);
	msg.append("\t   PASS <Password>\n");
	msg.append(GREEN);
	msg.append("STEP 2 -> ");
	msg.append(RESET);
	msg.append("Set a nickname:\n");
	msg.append(BOLD);
	msg.append("\t   NICK <nick>\n");
	msg.append(GREEN);
	msg.append("STEP 3 -> ");
	msg.append(RESET);
	msg.append("Set a username and fullname:\n");
	msg.append(BOLD);
	msg.append("\t   USER <user> * * :<fullname>\n");

	msg.append("\nOther commands:\n");
	msg.append(RESET);
	msg.append(GREEN);
	msg.append("-> OPER:\n");
	msg.append(RESET);
	msg.append("\t- Gain operator privileges\n");
	msg.append(GREEN);
	msg.append("-> JOIN ");
	msg.append(RESET);
	msg.append(BOLD);
	msg.append("<channel>:\n");
	msg.append(RESET);
	msg.append("\t- Joins a channel\n");
	msg.append(GREEN);
	msg.append("-> PRIVMSG ");
	msg.append(RESET);
	msg.append(BOLD);
	msg.append("<nick/channel> <message>:\n");
	msg.append(RESET);
	msg.append("\t- Sends a private message\n");
	msg.append(GREEN);
	msg.append("-> PING:\n");
	msg.append(RESET);
	msg.append("\t- Pings the server\n");
	msg.append(GREEN);
	msg.append("-> KICK ");
	msg.append(RESET);
	msg.append(BOLD);
	msg.append("<channel> <user>:\n");
	msg.append(RESET);
	msg.append("\t- Kicks a user from a channel\n");
	msg.append(GREEN);
	msg.append("-> INVITE ");
	msg.append(RESET);
	msg.append(BOLD);
	msg.append("<nick> <channel>:\n");
	msg.append(RESET);
	msg.append("\t- Invite a user to a channel\n");
	msg.append(GREEN);
	msg.append("-> TOPIC ");
	msg.append(RESET);
	msg.append(BOLD);
	msg.append("<channel> <topic>:\n");
	msg.append(RESET);
	msg.append("\t- Sets the channel topic\n");
	msg.append(GREEN);
	msg.append("-> MODE ");
	msg.append(RESET);
	msg.append(BOLD);
	msg.append("<channel/user> <mode>:\n");
	msg.append(RESET);
	msg.append("\t- Changes mode of a channel or user\n");
	msg.append(GREEN);
	msg.append("-> QUIT:\n");
	msg.append(RESET);
	msg.append("\t- Disconnects from the server\n");
	msg.append(GREEN);
	msg.append("-> PART ");
	msg.append(RESET);
	msg.append(BOLD);
	msg.append("<channel>:\n");
	msg.append(RESET);
	msg.append("\t- Leaves a channel\n\n");
	return (msg);
}
