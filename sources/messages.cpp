/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 08:05:47 by apereira          #+#    #+#             */
/*   Updated: 2024/10/13 13:28:47 by andrealbuqu      ###   ########.fr       */
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
	msg.append("Login to start chatting OR send HELP to see how :)\n");
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
