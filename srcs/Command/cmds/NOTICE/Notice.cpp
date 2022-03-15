#include "Notice.hpp"

// Constructor & Destructor

Notice::Notice() {
	this->_name = "NOTICE";
}

Notice::~Notice() {}

// Public function

void	Notice::execute() {

	if (this->_sender->_registered == false)
		throw ERR_RESTRICTED;

	if (this->getUser()) {
		User*		user = this->getUser();
		std::string	msg = this->_sender->getPrefix() + " " + this->getName() + " " + user->_nickname + " :" + this->makeString();
		
		user->getReply(msg);
	}
	else	
		this->_sender->getReply("Error: nick or channel doesn't exist");
	this->_args.erase(this->_args.begin(), this->_args.end());
}

// Private function

User*	Notice::getUser() {

	if (this->_args.empty())
		return NULL;
	else {
		std::map<int, User *>::iterator	it = this->_server->_user_lst.begin();
		std::map<int, User *>::iterator	ite = this->_server->_user_lst.end();

		for (; it != ite; ++it)
			if (it->second->_nickname == this->_args[1])
				return it->second;
	}
	return NULL;
}

std::string	Notice::makeString() {
	
	std::string	tmp;

	for (size_t i = 2; i <= this->_args.size(); i++) {
		if (!this->_args[i].empty()) {
			if (tmp.empty())
				tmp = this->_args[i].substr(1, this->_args[2].size());
			else
				tmp = tmp + " " + this->_args[i];
		}
	}
	tmp.erase(tmp.find_last_not_of(CRLF) + 1);
	return tmp;
}