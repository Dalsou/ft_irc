#ifndef NOTICE_HPP
#define NOTICE_HPP

#include "../Command.hpp"

class Notice : public Command {

	private:
		User*	getUser();
		std::string	makeString();

	public:
		Notice();
		~Notice();
		void execute();
};

#endif