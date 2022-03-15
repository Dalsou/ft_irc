#ifndef SERVER_HPP
#define SERVER_HPP

class Server;

#include "../ircserv.hpp"
#include "../User/User.hpp"
#include "../Channel/Channel.hpp"
#include "../Command/CmdHandler.hpp"
#include "../Command/Message.hpp"



class Server {

	private:

		std::string							_name;
		unsigned int						_port;
		std::string							_password;
		int									_sock;
		int									_host;
		std::vector<pollfd>					_fd_lst;


		Server();
		Server(const Server& src);
		const Server& operator=(const Server& op);

		int		acceptClient();
		int		receiveMsg(int index);
		void	handleCmd(int client_fd, const Message& msg);

	public:

		std::map<int, User *>				_user_lst;
		std::vector<Channel *>				_chan_lst;

		Server(std::string name, unsigned int port, std::string password);
		~Server();

		std::string		getName() const;
		unsigned int	getPort() const;
		std::string		getPassword() const;
		Channel*		getChannel(std::string chanName);
		User*			getUser(std::string userName);

		int		setUp();
		int		start();
		void	stop();

		bool	checkPass(std::string password);

		Channel*	createChannel(std::string channelName, User* op);
		void		deleteChannel(Channel* channel);

		void		removeUser(User* user);
};

#endif