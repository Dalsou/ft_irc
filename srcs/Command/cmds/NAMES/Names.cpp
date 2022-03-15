#include "Names.hpp"

// Constrcutor & Destructor 

Names::Names() {
	this->_name = "NAMES";
}

Names::~Names() {}

// Public function

void	Names::execute() {

	if (this->_sender->_registered == false)
		throw ERR_RESTRICTED;

	std::string	chanName;

	if (this->_args.size() < 2)
		chanName = "*";
	else
		chanName = this->_args[1];

	Channel*	channel;
	channel = this->_server->getChannel(chanName);

	std::map<int, User *>			users = this->_server->_user_lst;
	std::map<int, User *>::iterator	it = users.begin();
	std::map<int, User *>::iterator ite = users.end();

	for (; it != ite; ++it) {
		std::string reply = "353 * #" + (*it->second)._realname;
		this->_sender->getReply(reply);
	}
	this->_sender->getReply("366 * :End of NAMES list");
}