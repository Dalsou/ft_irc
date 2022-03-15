#ifndef LIST_HPP
#define LIST_HPP

#include "../Command.hpp"

class List : public Command {

	public :
		List();
		~List();
		void execute();
};

#endif