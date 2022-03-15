#include "Nick.hpp"

Nick::Nick() {
	this->_name = "NICK";
}

Nick::~Nick() {}

void	Nick::execute() {

	if (this->_sender->_passwordOK == false)
		return ;

	std::string	oldNick = this->_sender->_nickname;
	std::string newNick = this->_args[1];
	// check si nick deja pris à faire

	if (oldNick != "")
		this->_sender->sendMsg(this->_sender, "NICK " + newNick.substr(0, 9));
	this->_sender->setNickname(newNick);
	if (this->_sender->_registered == false)
		this->registerUser(this->_sender);
}

void Nick::registerUser(User* usr) {

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