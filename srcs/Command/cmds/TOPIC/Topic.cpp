#include "Topic.hpp"

// Constructor & Destructor

Topic::Topic() {
	this->_name = "TOPIC";
}

Topic::~Topic() {}

// Public Function

void	Topic::execute() {

	if (this->_args.size() < 2)
		throw ERR_NEEDMOREPARAMS(this->_name);

	Channel*	channel;
	channel = this->_server->getChannel(this->_args[1]);

	if (!channel)
		throw ERR_NOSUCHCHANNEL(this->_args[1]);

	if (this->_args.size() == 3)
		channel->setTopic(this->_args[2].substr(1, this->_args[2].size()));
	std::string reply;
	reply = ":ircserv 332 " + this->_sender->_nickname + " #" + channel->getName() + " :" + channel->getTopic();
	this->_sender->getReply(reply);
}