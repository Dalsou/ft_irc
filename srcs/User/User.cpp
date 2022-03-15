#include "User.hpp"

User::User(int fd, sockaddr_in new_socket) :
_socket(new_socket), _socketFd(fd), _registered(false), _passwordOK(false) {
	std::cout << COLOR_GREEN << "[<- New Client: " << inet_ntoa(this->_socket.sin_addr) << COLOR_RESET << std::endl;
}

User::~User() {}

// * ****** Setter ****** * //

void	User::setNickname(std::string nickname) {
	this->_nickname = nickname.substr(0, 9);
}

void	User::setUsername(std::string username) {
	this->_username = username;
}
void	User::setRealname(std::string realname) {
	this->_realname = realname;
}

// * ****** Getter ****** * //

std::string	User::getPrefix() {
	std::string	prefix;
	prefix = ":" + this->_nickname + "!@ircserv";
	return prefix; 
}

// * ****** Member functions ****** * //

void	User::removeUsrFromChannel(Channel* channel) {
	
	std::vector<Channel *>::iterator it = this->_channels.begin();
	std::vector<Channel *>::iterator ite = this->_channels.end();

	for (; it != ite; ++it)
		if (channel == (*it))
			this->_channels.erase(it);
	channel->removeUser(this);
}

void	User::appendMsg(std::string msg) {
	this->_msg.append(msg);
	this->_msg.erase(this->_msg.find_last_not_of("\r\n") + 1);
	this->_msg.append("\n");
}

void	User::clearMsg() {
	this->_msg.clear();
}

void	User::getReply(std::string msg) {
	std::string	finalMsg;

	finalMsg = msg + "\r\n";
	send(this->_socketFd, finalMsg.c_str(), finalMsg.length(), 0);
}

Channel*	User::getChannelByName(std::string chanName) {

	std::vector<Channel *>::iterator	it = this->_channels.begin();
	std::vector<Channel *>::iterator	ite = this->_channels.end();

	for (; it != ite; ++it) {
		if (chanName == (*it)->getName())
			return (*it);
	}
	return NULL;
}

void	User::sendMsg(User* receiver, std::string msg) {
	std::string tmpMsg;

	tmpMsg = this->getPrefix() + " " + msg;
	receiver->getReply(tmpMsg);
}