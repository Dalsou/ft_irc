#include "Ping.hpp"

Ping::Ping() {
	this->_name = "PING";
}

Ping::~Ping() {}

void	Ping::execute() {

	if (this->_args.size() < 2)
		throw ERR_NEEDMOREPARAMS(this->_name);

	std::string reply = "PONG " + this->_args[1] + CRLF;
	this->_sender->getReply(reply);
}