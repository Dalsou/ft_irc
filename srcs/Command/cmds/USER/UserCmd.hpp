#ifndef USERCMD_HPP
#define USERCMD_HPP

#include "../Command.hpp"

class UserCmd : public Command {

	private:
		void registerUser(User* user);
	public:
		UserCmd();
		virtual ~UserCmd();
		void execute();
};

#endif