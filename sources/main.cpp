/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apereira <apereira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:32:24 by andre-da          #+#    #+#             */
/*   Updated: 2024/10/01 07:28:32 by apereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.hpp"

int	is_port_valid(std::string port_nbr)
{
	if (port_nbr.empty())
	{
        std::cerr << "Error: no port was provided.\n";
        exit(1);
    }
	int	port;
	try
	{
        port = std::atoi(port_nbr.c_str());
	}
	catch (const std::invalid_argument& e)
	{
        std::cerr << "Invalid port number: " << port_nbr << "\n";
        exit(1);
    }
	if (port <= 1024 || port > 65535)
	{
        std::cerr << "Port number must be between 1024 and 65535.\n";
        exit(1);
    }
	return (1);
}

// Compare our project against Weechat (terminal-based)
int	main(int ac, char **av)
{
	if (ac != 3)
	{
		std::cout << "Usage: " << av[0] << " <port number> <password>" << std::endl;
		return (1);
	}
	std::cout << "---- SERVER ----" << std::endl;
	if(!is_port_valid(av[1]) || !*av[2])
	{
		std::cout << "invalid Port number / Password!" << std::endl;
		return (1);
	}
	// Começar a inicializar o server
	return (0);
}
