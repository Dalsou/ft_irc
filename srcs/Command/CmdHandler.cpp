#include "CmdHandler.hpp"

#include "cmds/CAP/Cap.hpp"
#include "cmds/INVITE/Invite.hpp"
#include "cmds/JOIN/Join.hpp"
#include "cmds/KICK/Kick.hpp"
#include "cmds/LIST/List.hpp"
#include "cmds/MODE/Mode.hpp"
#include "cmds/NAMES/Names.hpp"
#include "cmds/NICK/Nick.hpp"
#include "cmds/NOTICE/Notice.hpp"
#include "cmds/PART/Part.hpp"
#include "cmds/PASS/Pass.hpp"
#include "cmds/PING/Ping.hpp"
#include "cmds/PRIVMSG/PrivMsg.hpp"
#include "cmds/QUIT/Quit.hpp"
#include "cmds/TOPIC/Topic.hpp"
#include "cmds/USER/UserCmd.hpp"

// Cosntructor & Destructor

CmdHandler::CmdHandler(Server* server) :
_server(server) {
	this->_cmds_lst.push_back(new Cap());
	this->_cmds_lst.push_back(new Invite());
	this->_cmds_lst.push_back(new Join());
	this->_cmds_lst.push_back(new Kick());
	this->_cmds_lst.push_back(new List());
	this->_cmds_lst.push_back(new Mode());
	this->_cmds_lst.push_back(new Names());
	this->_cmds_lst.push_back(new Nick());
	this->_cmds_lst.push_back(new Notice());
	this->_cmds_lst.push_back(new Part());
	this->_cmds_lst.push_back(new Pass());
	this->_cmds_lst.push_back(new Ping());
	this->_cmds_lst.push_back(new PrivMsg());
	this->_cmds_lst.push_back(new Quit());
	this->_cmds_lst.push_back(new Topic());
	this->_cmds_lst.push_back(new UserCmd());
}

CmdHandler::~CmdHandler() {

	std::vector<Command *>::iterator	it = this->_cmds_lst.begin();
	std::vector<Command *>::iterator	ite = this->_cmds_lst.end();

	for (; it != ite; ++it)
		delete *it;
	this->_cmds_lst.clear();
}

// Public Function

void	CmdHandler::execCmd(User* sender, const Message& msg) {

	std::deque<std::string>	args = msg.getAv();

	if (!args.empty() && this->isCommand(args[0])) {
		
		std::string cmdName = args[0];
		args.front();
		for (size_t i = 0; i < this->_cmds_lst.size(); i++) {
			if (cmdName == this->_cmds_lst[i]->getName()) {
				this->_cmds_lst[i]->setServer(this->_server);
				this->_cmds_lst[i]->setSender(sender);
				this->_cmds_lst[i]->setArgs(args);
				try {
					this->_cmds_lst[i]->execute();
				} catch(const char* error_msg) {
					sender->getReply(std::string(error_msg));
				} catch(std::string error_msg) {
					sender->getReply(error_msg);
				}
				break ;
			}
		}
	}
}

// Private Function

bool	CmdHandler::isCommand(std::string cmdName) {
	
	std::vector<Command *>::iterator	it = this->_cmds_lst.begin();
	std::vector<Command *>::iterator	ite = this->_cmds_lst.end();

	for (; it != ite; ++it) 
		if ((*it)->getName() == cmdName)
			return true;
	return false;
}