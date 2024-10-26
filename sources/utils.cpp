/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:32:11 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/26 11:31:01 by andrealbuqu      ###   ########.fr       */
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

/* Displays messages */
void	Server::printMessage(int input, int index)
{
	std::string	msg;
	std::string wMsg;

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
			msg.append(std::to_string(port));
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
			msg.append(std::to_string(clients[index].getSocket()));
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
			msg.append(std::to_string(index));
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
			msg.append(GREEN);
			msg.append("\n001: Realname assigned: ");
			msg.append(RESET);
			msg.append(clients[index].getRealname());
			msg.append(CYAN);
			msg.append("\n001 :Welcome to the Internet Relay Chat Network, ");
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
