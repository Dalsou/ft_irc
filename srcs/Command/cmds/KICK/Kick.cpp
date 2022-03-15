#include "Kick.hpp"

Kick::Kick() {
	this->_name = "KICK";
}

Kick::~Kick() {}

void	Kick::execute() {

	if (this->_sender->_registered == false)
		throw ERR_RESTRICTED;
	if (this->_args.size() < 3)
		throw ERR_NEEDMOREPARAMS(this->_name);

	Channel* channel;
	channel = this->_server->getChannel(this->_args[1]);
	if (!channel)
		throw ERR_NOSUCHCHANNEL(this->_args[1]);
	if (!channel->getUser(this->_sender->_nickname))
		throw ERR_NOTONCHANNEL(channel->getName());

	User*	user;
	user = channel->getUser(this->_args[2]);
	if (!user)
		throw ERR_USERNOTINCHANNEL(this->_args[2], channel->getName());
	
	std::string	reply; 
	reply = this->_sender->getPrefix() + " " + this->_name + " #" + channel->getName() + " " + user->_nickname + " :" + this->_args[3];
	user->getReply(reply);
	this->sendReply(channel, reply);
	user->removeUsrFromChannel(channel);
}

void	Kick::sendReply(Channel* channel, std::string msg) const {

	std::vector<User *>				user_lst = channel->getUsers();
	std::vector<User *>::iterator	it = user_lst.begin();
	std::vector<User *>::iterator	ite = user_lst.end();

	for (; it != ite; ++it)
		(*it)->getReply(msg);
}

