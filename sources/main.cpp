/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:32:24 by andre-da          #+#    #+#             */
/*   Updated: 2024/10/03 16:42:29 by andrealbuqu      ###   ########.fr       */
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

bool	initServerTest(char *argv[])
{
	int					server_fd, client_fd;
	struct sockaddr_in	server_addr, client_addr;
	socklen_t			client_addr_len = sizeof(client_addr);
	char				buffer[1024];
	int					port = std::stoi(argv[2]);

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
		return (perror("socker"), 1);

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port);

	if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
		return (perror("bind"), close(server_fd), false);

	if (listen(server_fd, 5) < 0)
		return (perror("listen"), close(server_fd), false);

	std::cout << "Server listening on port " << port << std::endl;

	client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);

	if (client_fd < 0)
		return (perror("accept"), close(server_fd), false);

	std::cout << "Client connected" << std::endl;

	while (true)
	{
		ssize_t	bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
		if (bytes_read < 0)
			return (perror("read"), close(client_fd), close(server_fd), 1);

		buffer[bytes_read] = '\0';
		std::cout << "Received message: " << buffer;
	}
	close(client_fd);
	close(server_fd);
	return (true);
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
	if(!is_port_valid(av[1]) || av[2][0] == '\0')
	{
		std::cout << "invalid Port number / Password!" << std::endl;
		return (1);
	}
	// Começar a inicializar o server
	if (!initServerTest(av))
		return (1);

	return (0);
}
