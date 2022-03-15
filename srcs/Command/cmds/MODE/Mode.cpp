#include "Mode.hpp"

Mode::Mode() {
	this->_name = "MODE";
}

Mode::~Mode() {}

void	Mode::execute() {
	
	if (this->_args.size() < 3)
		throw ERR_NEEDMOREPARAMS(this->_name);
	
	if (this->_args[1][0] == '#') {
		int res = modeChan();
		if (res == 1)
			throw ERR_NOSUCHCHANNEL(this->_args[1].substr(1, this->_args[1].size()));
		if (res == 2)
			throw ERR_CHANOPRIVSNEEDED(this->_args[1].substr(1, this->_args[1].size()));
		if (res == 3)
			throw ERR_NOTONCHANNEL(this->_args[1].substr(1, this->_args[1].size()));
		if (res == 4)
			throw "Error: This channel has already the mode you've chose\n";
		if (res == 5)
			throw "Error: Wrong arguments\n";
	}	
	else {
		modeUser();
	}
}

int		Mode::modeChan() {

	Channel* channel = this->_server->getChannel(this->_args[1].substr(1, this->_args[1].size()));
	std::string mode = this->_args[2];
	int	choice;
	int res;

	if (!channel)
		return 1;
	if (!(channel->getOperator(this->_sender->_nickname)))
		return 2;

	if (mode[0] == '+')
		choice = 1;
	else if (mode[0] == '-')
		choice = 0;
	else
		return 5;

	if (mode[1] == 'i') {
		if ((res = channel->setOnlyInvitation(this->_sender, choice)))
			return res + 2;
	}
	else if (mode[1] == 'o') {
		if (this->_args.size() < 4)
			return 5;
		if ((res = channel->tryAddOperator(this->_args[3], choice)))
			return res + 2;
	}
	else
		return 5;

	return 0;
}

int		Mode::modeUser() {
	return 0;
}