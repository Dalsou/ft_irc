#include "Pass.hpp"

Pass::Pass() {
	this->_name = "PASS";
}

Pass::~Pass() {}

void	Pass::execute() {
	if (this->_sender->_registered == true)
		throw ERR_ALREADYREGISTRED;
	if (this->_args.size() < 2)
		throw ERR_NEEDMOREPARAMS(this->_name);

	std::string password;
	password = this->_args[1];
	if (this->_server->checkPass(password) == false)
		throw ERR_PASSWDMISMATCH;
	this->_sender->_passwordOK = true;
}