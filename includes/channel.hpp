#ifndef CHANNEL_CLASS_HPP
#define CHANNEL_CLASS_HPP

// Forward declarations
class Client;
class Server;

#include "headers.hpp"

class Channel
{
private:
	typedef std::map<std::string, Client *> t_nickMapClient;

	t_nickMapClient			clients;
	t_nickMapClient			invited;
	std::vector<Client*>	operators;
	std::string				mode;
	std::string				name;
	std::string				key;
	std::string				topic;
	int						usersLimit;
	int						usersCount;


public:
	Channel();
	Channel(const Channel &src);
	Channel(std::string mode, std::string name, Client *op);
	~Channel();

	Channel &operator=(const Channel &src);

	void			addClient(Client *client);
	bool			isMember(Client *client);
	void			removeClient(Client *client);
	void			sendMessage(const std::string &source, const std::string &command, const std::string &args);
	void			privateMessage(const std::string &source, const std::string &command, const std::string &args);
	bool    		isEmpty(void);
	std::string		getPrefix(Client *client) const;
	bool			isInvited(Client *client);
	std::string		addMode(const std::string &mode);
	std::string		delMode(const std::string &mode);
	void			addInvited(Client *client);
	void			delInvited(Client *client);

	// Operator methods
	bool			isOperator(Client *client) const;
	bool			addOperator(Client* client);
	bool			removeOperator(Client* client);

	const std::string		&getName(void) const;
	void					setName(const std::string &src);
	const t_nickMapClient	&getClients(void) const;
	void					setClients(t_nickMapClient &src);
	const std::string		&getKey(void) const;
	void					setKey(std::string &src);
	const std::string		&getTopic(void) const;
	void					setTopic(const std::string &src);
	std::string				getSymbol(void) const;
	void					setInvited(t_nickMapClient &src);
	const t_nickMapClient	&getInvited(void) const;
	const std::string		&getMode(void) const;
	void					setMode(std::string &src);
	int 					getUserLimit() const;
	void					setUserLimit(int limit);
	void 					removeUserLimit();
	int 					getUserCount() const;
	void					setUserCount(int count);

	std::ostream &operator<<(std::ostream &o) const;
};

std::ostream &operator<<(std::ostream &o, const Channel &src);

#endif
