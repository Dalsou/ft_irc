#ifndef TOPIC_HPP
#define TOPIC_HPP

#include "../Command.hpp"

class Topic : public Command {

	public:
		Topic();
		~Topic();
		void execute();
};

#endif