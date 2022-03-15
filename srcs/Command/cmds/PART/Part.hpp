#ifndef PART_HPP
#define PART_HPP

#include "../Command.hpp"

class Part : public Command {
	
	private:
		void sendReply(Channel* channel, std::string msg) const;
		
	public :
		Part();
		virtual ~Part();
		void execute();
};

#endif