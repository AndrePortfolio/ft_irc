/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:32:24 by andre-da          #+#    #+#             */
/*   Updated: 2024/10/08 17:19:43 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/headers.hpp"

int	main(int ac, char **av)
{
	try
	{
		if (ac != 3)
			throw std::runtime_error("Usage: ./ircserv <port number> <password>");

		std::cout << GREEN << "------------------- SERVER -------------------\n\n" << RESET;

		Server	server(av[1], av[2]);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}


/*
	struct sockaddr_in
	{
		short sin_family;			// must be AF_INET (refers to TCP & UDP family)
		unsigned short sin_port;	// port number
		struct in_addr sin_addr;	// ip address of the machine
		char sin_zero[8];			// make struct the same size as struct sockaddr_in
	};
*/

bool	initServerTest(char *argv[])
{
	int					server_fd, client_fd;
	struct sockaddr_in	server_addr, client_addr;
	socklen_t			client_addr_len = sizeof(client_addr);
	char				buffer[1024];
	int					port = std::stoi(argv[1]);

	// socket is assigned (status unbound)
	server_fd = socket(AF_INET, SOCK_STREAM, 0);	// TCP (more secure)
	if (server_fd < 0)
		return (perror("socket"), 1);

	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port);	// htons return the value in TCP/IP network byte order

	// Bind the IP address and port number to the socket (status bound)
	if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
		return (perror("bind"), close(server_fd), false);

	// Now that it is bound we can listen for requests from clients to connect
	// throught the port (status listening)
	if (listen(server_fd, 5) < 0)
		return (perror("listen"), close(server_fd), false);

	std::cout << "Server listening on port " << port << std::endl;

	// If accepted server duplicates his socket to connect the client (status connected)
	// the origin socket still is in (status listening) for new clients (that why it returns)
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
