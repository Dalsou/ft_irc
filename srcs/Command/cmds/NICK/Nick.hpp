#ifndef NICK_HPP
#define NICK_HPP

#include "../Command.hpp"

class Nick : public Command {

	private:
		void registerUser(User* user);
	public:
		Nick();
		virtual ~Nick();
		void execute();
};

#endif