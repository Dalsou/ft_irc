#include "UserCmd.hpp"

UserCmd::UserCmd() {
	this->_name = "USER";
}

UserCmd::~UserCmd() {}

void	UserCmd::execute() {

	if (this->_sender->_passwordOK == false)
		return ;
	if (this->_args.size() < 5)
		throw ERR_NEEDMOREPARAMS(this->_name);
	this->_sender->setUsername(this->_args[1]);
	this->_sender->setRealname(this->_args[4]);
	if (this->_sender->_registered == false)
		this->registerUser(this->_sender);
}

void	UserCmd::registerUser(User* usr) {

	usr->_registered = true;
	std::stringstream ss;

	ss << ":" << "ircserv" << " " << RPL_WELCOME << " " << usr->_nickname << " Welcome to the Internet Relay Network " \
		<< usr->_nickname << "!" << usr->_realname << "@ircserv" << CRLF;
	send(usr->_socketFd, ss.str().c_str(), ss.str().size(), 0);
	ss.str("");

	ss << ":" << "ircserv" << " " << RPL_YOURHOST << " " << usr->_nickname << " Your host is ircserv, running version 1.0" << CRLF;
	send(usr->_socketFd, ss.str().c_str(), ss.str().size(), 0);
	ss.str("");

	ss << ":" << "ircserv" << " " << RPL_CREATED << " " << usr->_nickname << " " << "This server was created 2022/16/02" << CRLF;
	send(usr->_socketFd, ss.str().c_str(), ss.str().size(), 0);
	ss.str("");

	ss << ":" << "ircserv" << " " << RPL_MYINFO << " " << usr->_nickname << " " << RPL_MYINFO_MSG << CRLF;
	send(usr->_socketFd, ss.str().c_str(), ss.str().size(), 0);

	std::cout << COLOR_GREEN << usr->_nickname << " succesfully registered !" << COLOR_RESET << std::endl;
}