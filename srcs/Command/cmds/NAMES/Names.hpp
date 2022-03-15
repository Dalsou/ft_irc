#ifndef NAMES_HPP
#define NAMES_HPP

#include "../Command.hpp"

class Names : public Command {

	public:
		Names();
		~Names();
		void execute();
};

#endif