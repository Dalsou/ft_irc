#ifndef NICK_HPP
#define NICK_HPP

#include "../Command.hpp"

class Nick : public Command {

	private:
		void registerUser(User* user);
		void sendReply(std::string msg) const;
		
	public:
		Nick();
		virtual ~Nick();
		void execute();
};

#endif