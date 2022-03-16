#include "List.hpp"

List::List() {
	this->_name = "LIST";
}

List::~List() {}

void	List::execute() {

	if (this->_sender->_registered == false)
		throw ERR_RESTRICTED;

	std::vector<Channel *> 				channels = this->_server->_chan_lst;
	std::vector<Channel *>::iterator	it = channels.begin();
	std::vector<Channel *>::iterator	ite = channels.end();

	for (; it != ite; ++it) {

		std::stringstream	ss;
		ss << "322 * #" << (*it)->getName() << " " << (*it)->getUsers().size();
		std::string reply = ss.str();
		this->_sender->getReply(reply);
	}
	this->_sender->getReply("323 * :End of LIST");
}