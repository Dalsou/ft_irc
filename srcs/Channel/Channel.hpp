#ifndef CHANNEL_HPP
#define CHANNEL_HPP

class Channel;

#include "../ircserv.hpp"
#include "../User/User.hpp"
#include "../Server/Server.hpp"

class	Channel {

	private:
		std::string			_name;
		std::vector<User *> _users;
		std::vector<User *> _operators;
		Server*				_server;
		std::string			_topic;
		bool				_onlyInvitation;
		std::vector<User *>	_invitations;

		Channel();

	public:
		// * ****** Constructor & Destructor ****** * //
		Channel(std::string name, User* firstOp, Server* server);
		~Channel();

		// * ****** Getter & Setter ****** * //
		void				setName(std::string newName);
		void				setTopic(std::string newTopic);
		int					setOnlyInvitation(User* user, int choice);
		std::string			getName() const;
		User*				getUser(std::string user);
		User*				getOperator(std::string op);
		std::vector<User *> getUsers() const;
		std::vector<User *> getOperators() const;
		std::string			getTopic();
		std::vector<User *>	getInvitations() const;
		bool				isUser(User* user);
		bool				isOperator(User* user);
		bool				hasInvitation(User* user);

		// * ****** Add & Remove functions ****** * //
		void				addUser(User* newUser);
		int					tryAddUser(User* newUser);
		void				removeUser(User* user);
		void				addOperator(User* newOp);
		int					tryAddOperator(std::string userNick, int choice);
		void				removeOperator(User* op);
		void				addInvitation(User* user);
		void				removeInvitation(User* user);

		// * ****** Message functions ****** * //
		void				sendMsgToChannel(User* sender, std::string msg, std::string cmdName);
};

#endif