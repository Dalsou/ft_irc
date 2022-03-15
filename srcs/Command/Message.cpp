#include "Message.hpp"

Message::Message(std::string raw_msg) :
raw_msg(raw_msg) {
	this->parseMsg();
}

Message::Message(std::string prefix, std::deque<std::string> av) :
prefix(prefix), av(av) {
	this->raw_msg = this->toRaw();
}

Message::~Message() {}

const std::string& Message::getRaw() const {
	return this->raw_msg;
}

const std::string& Message::getPrefix() const {
	return this->prefix;
}

const std::deque<std::string>& Message::getAv() const {
	return this->av;
}

void	Message::parseMsg() {

	std::string	msg;
	size_t		sub_len;

	msg = raw_msg;
	msg.erase(msg.find("\r\n", 0));
	while ((sub_len = msg.find(' ')) != std::string::npos) {
		if (msg[0] == ':' && this->av.size() > 0) {
			this->av.push_back(msg);
			msg.erase();
			break ;
		}
		this->av.push_back(msg.substr(0, sub_len));
		msg.erase(0, sub_len + 1);
	}
	if (!msg.empty())
		this->av.push_back(msg);
	if (this->av.size() > 0 && this->av[0][0] == ':') {
		this->av[0].erase(0, 1);
		this->prefix = this->av[0];
		this->av.erase(this->av.begin());
	}
}

std::string	Message::toRaw() {

	std::stringstream	raw;

	if (!this->prefix.empty())
		raw << ":" << this->prefix << " ";
	for (size_t i = 0; i < this->av.size(); ++i) {
		raw << this->av[i];
		if (i != this->av.size() - 1)
			raw << " ";
	}
	raw << "\r\n";
	return raw.str();
}