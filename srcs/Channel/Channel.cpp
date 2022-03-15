#include "Channel.hpp"

// * ****** Constructor & Destructor ****** * //

Channel::Channel(std::string name, User* firstOp, Server* server) :
_server(server) {
	this->setName(name);
	this->setTopic("");
	this->_operators.push_back(firstOp);
	this->_onlyInvitation = false;
}

Channel::~Channel() {}

// * ****** Getter & Setter ****** * //

void	Channel::setName(std::string name) {
	this->_name = name.substr(1, 200);
}

void	Channel::setTopic(std::string newTopic) {
	this->_topic = newTopic;
}

int		Channel::setOnlyInvitation(User* user, int choice) {

	if (!(this->getUser(user->_nickname)))
		return 1;
	if (this->_onlyInvitation == choice)
		return 2;
	this->_onlyInvitation = choice;
	return 0;
}

std::string		Channel::getName() const {
	return this->_name;
}

User*		Channel::getUser(std::string user) {
	std::vector<User *>::iterator it = this->_users.begin();
	std::vector<User *>::iterator ite = this->_users.end();

	for(; it != ite; ++it) {
		std::string current = (*it)->_nickname;
		if (current == user)
			return *it;
	}
	return NULL;
}

User*		Channel::getOperator(std::string op) {
	std::vector<User *>::iterator it = this->_operators.begin();
	std::vector<User *>::iterator ite = this->_operators.end();

	for(; it != ite; ++it) {
		std::string current = (*it)->_nickname;
		if (current == op)
			return *it;
	}
	return NULL;
}

std::vector<User *>	Channel::getUsers() const {
	return this->_users;
}

std::vector<User *>	Channel::getOperators() const {
	return this->_operators;
}

std::string	Channel::getTopic() {
	return this->_topic;
}

std::vector<User *> Channel::getInvitations() const {
	return this->_invitations;
}

bool	Channel::isUser(User* user) {
	std::vector<User *>::const_iterator	it = this->_users.begin();
	std::vector<User *>::const_iterator	ite = this->_users.end();

	for (; it != ite; ++it) 
		if (*it == user)
			return true;
	return false;
}

bool	Channel::isOperator(User* user) {
	std::vector<User *>::const_iterator	it = this->_operators.begin();
	std::vector<User *>::const_iterator	ite = this->_operators.end();

	for (; it != ite; ++it) 
		if (*it == user)
			return true;
	return false;
}

bool	Channel::hasInvitation(User* user) {

	std::vector<User *>::iterator	it = this->_invitations.begin();
	std::vector<User *>::iterator	ite = this->_invitations.end();

	for (; it != ite; ++it) 
		if (*it == user)
			return true;
	return false;
}

// * ****** Add & Remove functions ****** * //

void	Channel::addUser(User* newUser) {
	this->_users.push_back(newUser);
}

int		Channel::tryAddUser(User* newUser) {
	if (this->_onlyInvitation && this->hasInvitation(newUser) == false)
		return 1;
	else
		this->_users.push_back(newUser);
	return 0;
}

void	Channel::removeUser(User* user) {
	
	std::vector<User *>::iterator	it = this->_users.begin();
	std::vector<User *>::iterator	ite = this->_users.end();

	for (; it != ite; ++it) {
		if (*it == user) {
			this->_users.erase(it);
			break;
		}
	}
	if (this->_users.empty())
		this->_server->deleteChannel(this);
}

void	Channel::addOperator(User* newOp) {
	this->_operators.push_back(newOp);
}

int		Channel::tryAddOperator(std::string userNick, int choice) {

	User*	user;
	if (!(user = this->getUser(userNick)))
		return 1;
	if (choice == 1) {
		if (this->getOperator(user->_nickname))
			return 2;
		this->addOperator(user);
	}
	if (choice == 0) {
		if (!(this->getOperator(user->_nickname)))
			return 2;
		this->removeOperator(user);
	}
	return 0;
}

void	Channel::removeOperator(User* op) {
	std::vector<User *>::iterator	it = this->_operators.begin();
	std::vector<User *>::iterator	ite = this->_operators.end();

	for (; it != ite; ++it) {
		if (*it == op) {
			this->_operators.erase(it);
			break;
		}
	}
}

void	Channel::addInvitation(User* user) {
	this->_invitations.push_back(user);
}

void	Channel::removeInvitation(User* user) {

	std::vector<User *>::iterator it = this->_invitations.begin();
	std::vector<User *>::iterator ite = this->_invitations.end();

	for (; it != ite; ++it) {
		if (*it == user) {
			this->_invitations.erase(it);
			break ;
		}
	}
}

// * ****** Message function ****** * //

void	Channel::sendMsgToChannel(User* sender, std::string msg, std::string cmdName) {
	std::vector<User *>::iterator	it = this->_users.begin();
	std::vector<User *>::iterator	ite = this->_users.end();

	for (; it != ite; ++it)
		if (*it != sender)
			sender->sendMsg(*it, cmdName + " #" + this->getName() + " :" + msg + CRLF);
}