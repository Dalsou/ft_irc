#ifndef QUIT_HPP
#define QUIT_HPP

#include "../Command.hpp"

class Quit : public Command {

	private:
		void sendReply(Channel* channel, std::string msg) const;

	public:
		Quit();
		virtual ~Quit();
		void	execute();
};

#endif