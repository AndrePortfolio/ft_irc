/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:32:11 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/11/11 07:41:59 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/* Displays welcome message */
std::string	Server::welcomeMsg() const
{
	std::string msg = GREEN;
	msg.append("██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗\n");
	msg.append("██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝\n");
	msg.append("██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗\n");
	msg.append("██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝\n");
	msg.append("╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗\n");
	msg.append(" ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝\n");
	msg.append(BLUE);
	msg.append("\n✨ Login to start chatting OR type HELP to see all commands! ✨\n");
    msg.append("        📢 Remember: Great chat, great community! 🤗\n\n");
	msg.append(RESET);
	return (msg);
}

/* Displays message */
void	Server::printMessage(int input, int index)
{
	std::string	msg;
	std::string wMsg;
	std::ostringstream oss; // String stream for manual conversion

	switch (input)
	{
		case 0: // Init server
			msg.append(GREEN);
			msg.append("---------------------------- SERVER ----------------------------");
			msg.append(RESET);
			break;
		case 1: // Listening
			msg.append(CYAN);
			msg.append("[");
			msg.append(RESET);
			msg.append(currentDateTime());
			msg.append(CYAN);
			msg.append("]: ");
			msg.append(RESET);
			msg.append("listening on port ");
			oss.str("");  // Clear the stream
			oss << port;  // Convert the port number to string
			msg.append(oss.str());
			break;
		case 2: // New connection
			msg.append(GREEN);
			msg.append("[");
			msg.append(RESET);
			msg.append(currentDateTime());
			msg.append(GREEN);
			msg.append("]: ");
			msg.append(RESET);
			msg.append("new connection from ");
			msg.append(inet_ntoa(((sockaddr_in*)&clients[index].getAddress())->sin_addr));
			msg.append(" on socket ");
			oss.str("");  // Clear the stream
			oss << clients[index].getSocket();  // Convert socket to string
			msg.append(oss.str());
			msg.append(".");
			wMsg = welcomeMsg();
			send(clients[index].getSocket(), wMsg.c_str(), wMsg.length(), DEFAULT);
			break;
		case 3: // Disconnection
			msg.append(CYAN);
			msg.append("[");
			msg.append(RESET);
			msg.append(currentDateTime());
			msg.append(RED);
			msg.append("]: ");
			msg.append(RESET);
			msg.append("socket ");
			oss.str("");  // Clear the stream
			oss << index;  // Convert index to string
			msg.append(oss.str());
			msg.append(" hung up.");
			break;
		default:
			break;
	}
	std::cout << msg << std::endl;
}

/* Gets current time and date */
const std::string Server::currentDateTime()
{
	time_t		now = time(0);
	struct tm	tstruct;
	char		buf[80];
	tstruct = *localtime(&now);

	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
	return (buf);
}

std::string Server::feedbackClient(int input)
{
	std::string msg;

	msg.append(RED);
	switch (input)
	{
		case -1:
			msg.append("ERROR :Connection timeout");
			break ;
		case 381:
			msg.append(GREEN);
			msg.append("381: You are now an IRC operator.");
			break ;
		case 421:
			msg.append("461 :Unknown command or invalid parameter.");
			break ;
		case 431:
			msg.append("431 :No nickname given.");
			break ;
		case 432:
			msg.append("432 :Erroneous nickname.");
			break ;
		case 433:
			msg.append("433 :Nickname is already in use.");
			break ;
		case 436:
			msg.append("436 :Nickname collision KILL.");
			break ;
		case 461:
			msg.append("461 :Not enough parameters.");
			break ;
		case 462:
			msg.append("462 :You may not reregister.");
			break ;
		case 463:
			msg.append("463 :You are not authenticated.");
			break ;
		case 464:
			msg.append("464 :Password incorrect");
			break ;
		case 465:
			msg.append("465 :Invalid password provided.");
			break ;
		case 491:
			msg.append("491 :host not allowed OPER privileges.");
			break ;
		default:
			break ;
	}
	msg.append("\n");
	msg.append(RESET);
	return (msg);
}

const std::string Server::getMessage(int input, int index)
{
	std::string msg;

	msg.append(GREEN);
	switch (input)
	{
		case 0:
			msg.append("001: Correct password!");
			break;
		case 1:
			msg.append("001: Nickname assigned: ");
			msg.append(RESET);
			msg.append(clients[index].getNickname());
			break;
		case 2:
			msg.append("001: Username assigned: ");
			msg.append(RESET);
			msg.append(clients[index].getUsername());
			msg.append("\n");
			msg.append(GREEN);
			msg.append("001: Realname assigned: ");
			msg.append(RESET);
			msg.append(clients[index].getRealname());
			msg.append("\n");
			msg.append(CYAN);
			msg.append("001 :Welcome to the Internet Relay Chat Network, ");
			msg.append(RESET);
			msg.append(clients[index].getNickname());
			break;
		default:
			break ;
	}
	msg.append("\n");
	msg.append(RESET);
	return (msg);
}

void	Server::informOtherClients(int index, std::string nickname)
{
	std::string	msg;

	msg.append(CYAN);
	msg.append("<server> ");
	msg.append(RESET);
	msg.append(":");
	if (clients[index].getNickname() != "")
		msg.append(clients[index].getNickname());
	else
		msg.append(nickname);
	msg.append(CYAN);
	msg.append(" NICK ");
	msg.append(RESET);
	msg.append(":");
	msg.append(nickname);
	msg.append("\n");

	for (size_t i = 0; i < clients.size(); i++)
		if ((size_t)index != i)
			send(clients[i].getSocket(), msg.c_str(), msg.length(), DEFAULT);
}

void	Server::feedbackClients(int client, int clientID, std::string reason, Channel* channel)
{
	std::string outputMsg;

	outputMsg.append(CYAN);
	outputMsg.append("<server> ");
	outputMsg.append(RESET);
	outputMsg.append(":");
	outputMsg.append(clients[client].getNickname());
	outputMsg.append(CYAN);
	outputMsg.append(" QUIT ");
	outputMsg.append(channel->getName());
	outputMsg.append(RESET);
	outputMsg.append(" ");
	if (reason != "")
		outputMsg.append(reason);
	outputMsg.append("\n");
	send(clients[clientID].getSocket(), outputMsg.c_str(), outputMsg.length(), DEFAULT);
}
