#include "Command.hpp"

// Constructor & Destructor 

Command::Command() :
_name(""), _server(NULL), _sender(NULL) {}

Command::~Command() {}

std::string Command::getName() const {
	return this->_name;
}

// Setter

void	Command::setSender(User* sender) {
	this->_sender = sender;
}

void	Command::setServer(Server* server) {
	this->_server = server;
}

void	Command::setArgs(std::deque<std::string> args) {
	this->_args = args;
}

// Public Functions

std::vector<std::string>	Command::splitArgs(std::string& args, const char* delim) {

	std::vector<std::string>	res;
	size_t	i = 0;

	while (i < args.size()) {
		size_t	delimIdx = args.find(delim, i);

		if (delimIdx == std::string::npos)
			delimIdx = args.size();
		if ((delimIdx - i) > 0)
			res.push_back(args.substr(i, delimIdx - i));
		i = delimIdx + 1;
	}
	return res;
}