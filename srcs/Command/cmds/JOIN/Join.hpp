#ifndef JOIN_HPP
#define JOIN_HPP

#include "../Command.hpp"

class Join: public Command {

	private:
		void sendReply(Channel* channel, std::string msg) const;

	public :
		Join();
		virtual ~Join();
		void execute();
};

#endif