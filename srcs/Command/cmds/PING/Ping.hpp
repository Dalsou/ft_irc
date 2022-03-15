#ifndef PING_HPP
#define PING_HPP

#include "../Command.hpp"

class Ping : public Command {

	public :
		Ping();
		~Ping();
		void execute();
};

#endif