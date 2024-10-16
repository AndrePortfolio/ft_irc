/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:38 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/16 11:30:29 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/* Unsure of what this does, just replicating behavior from previous code */
std::string	Server::joinCommand(const strings& parameters, int& client)
{
	(void)parameters;
	(void)client;
	// if (commands.size() <= 1 || commands[1][0] != '#')
	// 	return (":server 461 * JOIN :No channel specified or invalid channel name\r\n");
	return (":nick!user@server JOIN " "+ channel +" "\r\n:server 332 " "+ channel +" " :Welcome to " "+ channel +" "\r\n");
}
