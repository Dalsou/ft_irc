#include "Quit.hpp"

// Constructor & Destructor

Quit::Quit() {
	this->_name = "QUIT";
}

Quit::~Quit() {}

// Function

void	Quit::execute() {

	std::string		msg;
	std::string		reply;
	std::vector<Channel *>::iterator	it = this->_server->_chan_lst.begin();
	std::vector<Channel *>::iterator	ite = this->_server->_chan_lst.end();

	reply = this->_sender->getPrefix() + " " + this->_name + " " + this->_args[1];
	for (; it != ite; ++it) {
		if ((*it)->isUser(this->_sender)) {
			this->sendReply(*it, reply);
			this->_sender->removeUsrFromChannel(*it);
		}
	}
}

void	Quit::sendReply(Channel* channel, std::string msg) const {

	std::vector<User *>				user_lst = channel->getUsers();
	std::vector<User *>::iterator	it = user_lst.begin();
	std::vector<User *>::iterator	ite = user_lst.end();

	for (; it != ite; ++it)
		if (this->_sender != (*it))
			(*it)->getReply(msg);
}