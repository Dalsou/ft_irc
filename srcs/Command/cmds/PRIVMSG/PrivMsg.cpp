#include "PrivMsg.hpp"

// Constructor & destructor

PrivMsg::PrivMsg() {
	this->_name = "PRIVMSG";
}

PrivMsg::~PrivMsg() {}

// Public function

void	PrivMsg::execute() {

	if (this->_sender->_registered == false)
		throw ERR_RESTRICTED;

	if (this->getUser()) {
		User*		user = this->getUser();
		std::string	msg = "PRIVMSG " + user->_nickname + " :" + this->makeString();
		
		this->_sender->sendMsg(user, msg);
	}
	else if (this->getChannel()) {
		Channel*	tmp_channel = this->getChannel();
		if (!(tmp_channel->getUser(this->_sender->_nickname)))
			throw ERR_CANNOTSENDTOCHAN(tmp_channel->getName());

		std::string	tmp_msg = this->makeString();

		std::cout << tmp_msg << std::endl;
		if (tmp_channel && !tmp_msg.empty())
			tmp_channel->sendMsgToChannel(this->_sender, tmp_msg, this->_name);
	}
	else	
		this->_sender->getReply("Error: nick or channel doesn't exist");
	this->_args.erase(this->_args.begin(), this->_args.end());
}

// Private function

User*	PrivMsg::getUser() {

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

Channel*	PrivMsg::getChannel() {

	if (this->_args.empty())
		return NULL;
	else {
		std::string	tmp_name;
		Channel*	channel;

		tmp_name = this->_args[1].substr(1, this->_args[1].size());
		if ((channel = this->_server->getChannel(tmp_name)) != NULL)
			return channel;		
	}
	return NULL;
}

std::string	PrivMsg::makeString() {
	
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
