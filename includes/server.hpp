/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:32:24 by andre-da          #+#    #+#             */
/*   Updated: 2024/10/08 17:57:03 by andrealbuqu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "headers.hpp"

class Client;

class Server
{
	private:
		int					port;
		std::string			password;
		bool				signal;
		int					socketFd;
		struct sockaddr_in	address;
		std::vector<Client>	clients;

		Server();

	public:
		Server(std::string port, std::string password);
		Server(const Server &copy);
		Server& operator=(const Server &other);
		~Server();

		void		validateInput(std::string port, std::string password);
		void		initServer();
		void		initServerAddress();
		void		setNonBlocking(int fd);
		void		configureSocketOptions(int fd);
		void		acceptClients();
		void		receivedNewData(int fd);

		static void	signalHandler(int signum);
		void		closeFds();
		void		clearClients(int fd);
};

#endif
