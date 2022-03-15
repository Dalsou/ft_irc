#ifndef PRIVMSG_HPP
#define PRIVMSG_HPP

#include "../Command.hpp"

class PrivMsg : public Command {

	private:
		User* getUser();
		Channel* getChannel();
		std::string	makeString();

	public:
		PrivMsg();
		~PrivMsg();
		void execute();
};

#endif