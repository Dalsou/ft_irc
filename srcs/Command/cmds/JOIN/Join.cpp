#include "Join.hpp"

// Constructor & destructor

Join::Join() {
	this->_name = "JOIN";
}

Join::~Join() {}

// Public Function

void	Join::execute() {

	if (this->_sender->_registered == false)
		throw ERR_RESTRICTED;
	if (this->_args.size() < 2)
		throw ERR_NEEDMOREPARAMS(this->_name);

	std::vector<std::string>	channels = splitArgs(this->_args[1], ",");
	for (size_t i = 0; i < channels.size(); ++i) {
		Channel*	channel;
		
		if (!(channel = this->_server->getChannel(channels[i]))) {
			channel = this->_server->createChannel(channels[i], this->_sender);
			channel->addUser(this->_sender);

			std::string	reply; 
			reply = this->_sender->getPrefix() + " " + this->_name + " #" + channel->getName();
			this->sendReply(channel, reply);
			return ;
		}	
		if (channel->tryAddUser(this->_sender))
			throw ERR_INVITEONLYCHAN(channel->getName());
		else {
			std::string	reply; 
			reply = this->_sender->getPrefix() + " " + this->_name + " #" + channel->getName();
			this->sendReply(channel, reply);
		}
	}
}

// Private Function

void	Join::sendReply(Channel* channel, std::string msg) const {

	std::vector<User *>				user_lst = channel->getUsers();
	std::vector<User *>::iterator	it = user_lst.begin();
	std::vector<User *>::iterator	ite = user_lst.end();

	for (; it != ite; ++it)
		(*it)->getReply(msg);
}