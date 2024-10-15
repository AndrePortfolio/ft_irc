/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cap.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:06:38 by andrealbuqu       #+#    #+#             */
/*   Updated: 2024/10/15 11:45:03 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers.hpp"

/* Unsure of what this does, just replicating behavior from previous code */
std::string	Server::capCommand(const strings& commands)
{
	(void)commands;
	// if (commands.size() == 3 && commands[1] == "LS" && commands[2] == "302")
		return ("CAP * LS :\n");
}
