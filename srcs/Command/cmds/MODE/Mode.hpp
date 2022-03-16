#ifndef MODE_HPP
#define MODE_HPP

#include "../Command.hpp"

class Mode : public Command {

	private:
		int modeChan();
		int modeUser();
		void sendReply(Channel* channel, std::string msg) const;

	public:
		Mode();
		~Mode();
		void execute();
};

#endif