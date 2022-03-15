#ifndef COMMAND_HPP
#define COMMAND_HPP

class Command;

#include "../../Server/Server.hpp"
#include "../../Channel/Channel.hpp"
#include "../../User/User.hpp"
#include "../../ircserv.hpp"

// Reply code

// Error code + message
#define ERR_NOSUCHNICK(nickname)				("401 * " + nickname + " :No such nick/channel")
#define ERR_NOSUCHCHANNEL(channel)				("403 * #" + channel + " :No such channel")
#define ERR_CANNOTSENDTOCHAN(channel)			("404 * #" + channel + " :Cannot send to channel")
#define ERR_UNKNOWNCOMMAN(command)				("421 * " + command + " :Unknown command")
#define ERR_NICKNAMEINUSE(nickname)				("433 * " + nickname + " :Nickname is already in use")
#define ERR_USERNOTINCHANNEL(nickname, channel)	("441 * " + nickname + " #" + channel + " :They aren't on that channel")
#define ERR_NOTONCHANNEL(channel)				("442 * " + channel + " :You're not on that channel")
#define ERR_USERONCHANNEL(nickname, channel)	("443 * " + nickname + " #" + channel + " :is already on channel")
#define ERR_NEEDMOREPARAMS(command)				("461 * " + command + " :Not enough parameters")
#define ERR_ALREADYREGISTRED					"462 * :Unauthorized command (already registered)"
#define ERR_PASSWDMISMATCH						"464 * :Password incorrect"
#define ERR_INVITEONLYCHAN(channel)				("473 * " + channel + ": Cannot join channel")
#define ERR_BADCHANMASK(channel)				("476 * #" + channel + " :Bad Channel Mask")
#define ERR_CHANOPRIVSNEEDED(channel)			("482 * #" + channel + " :You're not channel operator")
#define ERR_RESTRICTED							"484 * :Your connection is restricted!"

class Command {

	protected:
		std::string				_name; 
		Server*					_server;
		User*					_sender;
		std::deque<std::string>	_args;

	public:
		Command();
		virtual ~Command();

		std::string	getName() const;

		void	setSender(User* sender);
		void	setServer(Server* server);
		void	setArgs(std::deque<std::string> args);

		std::vector<std::string>	splitArgs(std::string& args, const char* delim);
		virtual void execute() = 0;
};

#endif