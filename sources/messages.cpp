/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 08:05:47 by apereira          #+#    #+#             */
/*   Updated: 2024/10/12 13:20:50 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/* Displays welcome message */
std::string	Server::welcomeMsg() const
{
	std::string welcome = GREEN;
	welcome.append("██╗    ██╗███████╗██╗      ██████╗ ██████╗ ███╗   ███╗███████╗\n");
	welcome.append("██║    ██║██╔════╝██║     ██╔════╝██╔═══██╗████╗ ████║██╔════╝\n");
	welcome.append("██║ █╗ ██║█████╗  ██║     ██║     ██║   ██║██╔████╔██║█████╗\n");
	welcome.append("██║███╗██║██╔══╝  ██║     ██║     ██║   ██║██║╚██╔╝██║██╔══╝\n");
	welcome.append("╚███╔███╔╝███████╗███████╗╚██████╗╚██████╔╝██║ ╚═╝ ██║███████╗\n");
	welcome.append(" ╚══╝╚══╝ ╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚═╝     ╚═╝╚══════╝\n");
	welcome.append(BLUE);
	welcome.append("You need to login so you can start chatting OR you can send HELP to see how :) \n");
	welcome.append(RESET);
	return (welcome);
}

/* Displays messages */
void	Server::printMessage(int input)
{
	std::string	msg;
	std::string welcome;

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
			msg.append(inet_ntoa(((sockaddr_in*)&clients.back().getAddress())->sin_addr));
			msg.append(" on socket ");
			msg.append(std::to_string(clients.back().getSocket()));
			msg.append(".");
			welcome = welcomeMsg();
			send(clients.back().getSocket(), welcome.c_str(), welcome.length(), DEFAULT);
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
			msg.append(std::to_string(clients.back().getSocket()));
			msg.append(" hung up.");
			break;
		default:
			break;
	}
	std::cout << msg << std::endl;
}
