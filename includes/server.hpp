/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrealbuquerque <andrealbuquerque@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:32:24 by andre-da          #+#    #+#             */
/*   Updated: 2024/10/03 15:54:25 by andrealbuqu      ###   ########.fr       */
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
		int					serviceSocketFd;
		static bool			signal;
		std::vector<Client>	clients;

	public:
		Server();
		Server(const Server &copy);
		Server& operator=(const Server &other);
		~Server();

		void		serverInit();
		void		createServerSocket();
		void		acceptNewClient();
		void		receivedNewData(int fd);
		static void	signalHandler(int signum);
		void		closeFds();
		void		clearClients(int fd);
};

#endif
