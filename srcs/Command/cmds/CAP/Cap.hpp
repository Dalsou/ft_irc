#ifndef CAP_HPP
#define CAP_HPP

#include "../Command.hpp"

class Cap : public Command {

	public :
		Cap();
		~Cap();
		void execute();
};

#endif