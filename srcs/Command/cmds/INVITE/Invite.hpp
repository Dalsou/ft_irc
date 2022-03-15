#ifndef INVITE_HPP
#define INVITE_HPP

#include "../Command.hpp"

class Invite : public Command {

	public:
		Invite();
		~Invite();
		void execute();
};

#endif