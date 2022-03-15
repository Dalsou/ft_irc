#ifndef MESSAGE_HPP
#define MESSAGE_HPP

class Message;

#include "../ircserv.hpp"

class Message {

	private:
		std::string					raw_msg;
		std::string					prefix;
		std::deque<std::string>		av;

		Message();
		Message(const Message& src);
		const Message& operator=(const Message& op);

		void		parseMsg();
		std::string toRaw();

	public:
		Message(std::string raw_msg);
		Message(std::string prefix, std::deque<std::string> av);
		~Message();

		const std::string&				getRaw() const;
		const std::string&				getPrefix() const;
		const std::deque<std::string>& getAv() const;

};

#endif