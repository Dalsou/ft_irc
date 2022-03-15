#ifndef KICK_HPP
#define KICK_HPP

#include "../Command.hpp"

class Kick : public Command {

	private:
		void sendReply(Channel* channel, std::string msg) const;

	public :
		Kick();
		~Kick();
		void execute();
};

#endif