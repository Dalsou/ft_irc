#include "Part.hpp"

// Constructor & Destructor

Part::Part() {
	this->_name = "PART";
}

Part::~Part() {}

// Public Function

void	Part::execute() {

	if (this->_sender->_registered == false)
		throw ERR_RESTRICTED;
	if (this->_args.size() < 1) 
		throw ERR_NEEDMOREPARAMS(this->_name);

	std::vector<std::string>	channels = splitArgs(this->_args[1], ",");
	for (size_t i = 0; i < channels.size(); ++i) {
		Channel*	channel;

		if (!(channel = this->_server->getChannel(channels[i])))
			throw ERR_NOSUCHCHANNEL(channels[i]);
		if (channel->isUser(this->_sender) == false)
			throw ERR_NOTONCHANNEL(channels[i]);
		
		std::string	reply;
		reply = this->_sender->getPrefix() + " " + this->_name + " #" + channel->getName();
		this->sendReply(channel, reply);
		this->_sender->removeUsrFromChannel(channel);
	}
}

// Private function

void	Part::sendReply(Channel* channel, std::string msg) const {
	
	std::vector<User *>				user_lst = channel->getUsers();
	std::vector<User *>::iterator	it = user_lst.begin();
	std::vector<User *>::iterator	ite = user_lst.end();

	for (; it != ite; ++it)
		(*it)->getReply(msg);
}