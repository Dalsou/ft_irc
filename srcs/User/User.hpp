#ifndef USER_HPP
#define USER_HPP

class User;

#include "../ircserv.hpp"
#include "../Channel/Channel.hpp"

class User {

    public:
		std::string				_nickname;
		std::string 			_username;
		std::string 			_realname;
		sockaddr_in				_socket;
		int						_socketFd;
		std::string				_buffer;
		bool					_registered;
		bool					_passwordOK;
		std::vector<Channel *>	_channels;
		std::string				_msg;

		// * ****** Constructor & Destructor ****** * //
        User(int fd, sockaddr_in socket);
        ~User();

		// * ****** Setter ****** * //
		void	setNickname(std::string nickname);
		void	setUsername(std::string username);
		void	setRealname(std::string realname);

		// * ****** Getter ****** * //
		std::string getPrefix();
		Channel*	getChannelByName(std::string chanName);

		void	getReply(std::string msg);
		void	removeUsrFromChannel(Channel* channel);
		void	appendMsg(std::string msg);
		void	clearMsg();
		void	sendMsg(User* receiver, std::string msg);
};

#endif