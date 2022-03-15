#include "Invite.hpp"

Invite::Invite() {
	this->_name = "INVITE";
}

Invite::~Invite() {}

void	Invite::execute() {

	if (this->_sender->_registered == false)
		throw ERR_RESTRICTED;
	if (this->_args.size() < 3)
		throw ERR_NEEDMOREPARAMS(this->_name);
	
	Channel* channel;
	channel = this->_server->getChannel(this->_args[2]);
	if (!channel)
		throw ERR_NOSUCHCHANNEL(this->_args[2]);
	if (!channel->getUser(this->_sender->_nickname))
		throw ERR_NOTONCHANNEL(channel->getName());

	User*	target;
	target = this->_server->getUser(this->_args[1]);
	if (!target)
		throw ERR_NOSUCHNICK(this->_args[1]);
	if (channel->getUser(target->_nickname) != NULL)
		throw ERR_USERONCHANNEL(target->_nickname, channel->getName());

	channel->addInvitation(target);
	
	std::string	reply_target; 
	reply_target = this->_sender->getPrefix() + " " + this->_name + " " + target->_nickname + " :#" + channel->getName();
	target->getReply(reply_target);

	std::string reply_sender = "341 * #" + channel->getName() + " " + target->_nickname;
	this->_sender->getReply(reply_sender);
}