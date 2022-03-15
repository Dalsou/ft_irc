#ifndef MODE_HPP
#define MODE_HPP

#include "../Command.hpp"

class Mode : public Command {

	private:
		int modeChan();
		int modeUser();

	public:
		Mode();
		~Mode();
		void execute();
};

#endif