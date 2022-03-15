#ifndef CMDHANDLER_HPP
#define CMDHANDLER_HPP

class CmdHandler;

#include "cmds/Command.hpp"
#include "../ircserv.hpp"
#include "../Server/Server.hpp"
#include "../User/User.hpp"
#include "Message.hpp"

class CmdHandler {

	private:
		Server*					_server;
		std::vector<Command *>	_cmds_lst;
		bool					isCommand(std::string cmdName);

	public:
		CmdHandler(Server* server);
		virtual ~CmdHandler();
		void	execCmd(User* sender, const Message& msg);
};

#endif