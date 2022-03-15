#ifndef PASS_HPP
#define PASS_HPP

#include "../Command.hpp"

class Pass : public Command {

	public:
		Pass();
		~Pass();
		void execute();
};

#endif