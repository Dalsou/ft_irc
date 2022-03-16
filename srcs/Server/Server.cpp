#include "Server.hpp"

// * ******* Constructor & Destructor ****** * //

Server::Server(std::string name, unsigned int port = 6667, std::string password = "") :
_name(name), _port(port), _password(password) {}

Server::~Server() {
	this->stop();
}

// * ****** Getter ****** * //

std::string		Server::getName() const {
	return this->_name;
}

unsigned int	Server::getPort() const {
	return this->_port;
}

std::string		Server::getPassword() const {
	return this->_password;
}

Channel*	Server::getChannel(std::string chanName) {

	std::string	tmp = chanName;
	if (tmp.c_str()[0] == '#')
		tmp = tmp.substr(1, tmp.size());
	
	std::vector<Channel *>::iterator	it = this->_chan_lst.begin();
	std::vector<Channel *>::iterator	ite = this->_chan_lst.end();

	for (; it != ite; ++it) {
		if ((*it)->getName() == tmp){
			return *it;
			break ;
		}
	}
	return NULL;
}

User*		Server::getUser(std::string userName) {

	std::map<int, User *>::iterator	it = this->_user_lst.begin();
	std::map<int, User *>::iterator	ite = this->_user_lst.end();

	for (; it != ite; ++it) {
		std::string	current = (*it->second)._nickname;
		if (current == userName)
			return it->second;
	}
	return NULL;
}

// * ****** Set Up & Start Functions ****** * //

int	Server::setUp() {

	sockaddr_in	address;
	int			opt;
	protoent*	prot(getprotobyname("tcp"));


	this->_fd_lst.push_back(pollfd());
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY; // 127.0.0.1
	address.sin_port = htons(this->_port);

	#ifdef __APPLE__
		if ((this->_fd_lst.front().fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	#else
		if ((this->_fd_lst.front().fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0)) == 0)
	#endif
	{
		perror("socket failed");
		return 1;
	}

	if ((fcntl(this->_fd_lst.front().fd, F_SETFL, O_NONBLOCK)) == -1) {
		perror("fcntl failed");
		return 1;
	}
	
	this->_fd_lst.front().events = POLLIN;

	#ifdef __APPLE__
		if (setsockopt(this->_fd_lst.front().fd, SOL_SOCKET, SO_REUSEADDR, &opt, prot->p_proto)) 
	#else
		if (setsockopt(this->_fd_lst.front().fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, prot->p_proto))
	#endif
	{
		perror("setsockopt failed");
		return 1;
	}
	
	if (bind(this->_fd_lst.front().fd, (struct sockaddr *)& address, sizeof(address)) == -1) {
		perror("bind failed");
		return 1;
	}

	if (listen(this->_fd_lst.front().fd, SOMAXCONN) == -1) {
		perror("listen failed");
		return 1;
	}
	std::cout << "IRC Server now active on port : " << this->_port << std::endl;
	
	return 0;
}

int	Server::start() {

	int		nfds_ready;

	while (true) {
		if ((nfds_ready = poll(&this->_fd_lst.front(), this->_fd_lst.size(), -1)) == -1) {
			perror("poll failed");
			return 1;
		}
		for (unsigned int i = 0; i < this->_fd_lst.size(); i++) {
			if (this->_fd_lst[i].revents == 0)
				continue ;
			if (this->_fd_lst[i].revents == POLLIN) {
				if (i == 0) {
					this->acceptClient();
					break ;
				}
				else
					this->receiveMsg(i);
			}
		}
	}
	return 0;
}

int	Server::acceptClient() {

	int			new_fd;
	sockaddr_in	new_socket;
	socklen_t	socket_len;

	while ((new_fd = accept(this->_fd_lst[0].fd, (sockaddr *)&new_socket, &socket_len)) != -1) {

		this->_fd_lst.push_back(pollfd());
		this->_fd_lst.back().fd = new_fd;
		this->_fd_lst.back().events = POLLIN;

		if (fcntl(new_fd, F_SETFL, O_NONBLOCK) == -1) {
			perror("fcntl failed");
			return 1;
		}

		this->_user_lst.insert(std::make_pair(new_fd, new User(new_fd, new_socket)));
	}
	if (errno != EWOULDBLOCK) {
		std::cerr << COLOR_RED << std::strerror(errno) << COLOR_RESET << std::endl;
		return (1);
	}
	return 0;
}

int	Server::receiveMsg(int index) {

	char	buffer[BUFFER_SIZE + 1];
	int		recv_bytes;

	memset(buffer, 0, BUFFER_SIZE + 1);
	if ((recv_bytes = recv(this->_fd_lst[index].fd, buffer, BUFFER_SIZE, 0)) == -1) {
		std::cerr << COLOR_RED << std::strerror(errno) << COLOR_RESET << std::endl;
		return 1;
	}
	if (recv_bytes == 0) {
		std::cout << COLOR_GREEN << "[-> Client quit: " << inet_ntoa(this->_user_lst[this->_fd_lst[index].fd]->_socket.sin_addr) << COLOR_RESET << std::endl;
		close(this->_fd_lst[index].fd);
		this->_user_lst.erase(this->_fd_lst[index].fd);
		this->_fd_lst.erase(this->_fd_lst.begin() + index);
	}
	else {
		std::string str_buff(buffer);
		this->_user_lst[this->_fd_lst[index].fd]->_buffer += str_buff;
		size_t	cmd_end;

		while ((cmd_end = this->_user_lst[this->_fd_lst[index].fd]->_buffer.find("\r\n", 0)) != std::string::npos) {
			Message msg(this->_user_lst[this->_fd_lst[index].fd]->_buffer.substr(0, cmd_end + 2));

			std::cout << msg.getRaw() << std::endl;
			this->handleCmd(this->_fd_lst[index].fd, msg);
			this->_user_lst[this->_fd_lst[index].fd]->_buffer.erase(0, cmd_end + 2);
		}
	}
	return 0;
}

void Server::handleCmd(int usr_fd, const Message& msg) {

	CmdHandler*	cmdHandler = new CmdHandler(this);
	User*		sender = this->_user_lst.find(usr_fd)->second;
	
	cmdHandler->execCmd(sender, msg);
}

void	Server::stop() {

	std::vector<pollfd>::iterator	fd_it;
	std::map<int, User *>::iterator	user_it;

	for (fd_it = this->_fd_lst.begin(); fd_it != this->_fd_lst.end(); ++fd_it)
		close(fd_it->fd);

	for (user_it = this->_user_lst.begin(); user_it != this->_user_lst.end(); ++user_it)
		delete user_it->second;
	this->_user_lst.clear();
}

bool	Server::checkPass(std::string password) {

	if (this->_password != password)
		return false;
	return true;
}

bool	Server::checkNickname(std::string nickname) {

	std::string						tmpNick = this->myToUpper(nickname);
	std::string						nick;
	std::map<int, User *>::iterator	it = this->_user_lst.begin();	
	std::map<int, User *>::iterator	ite = this->_user_lst.end();

	for (; it != ite ; ++it){
		nick = this->myToUpper((*it).second->_nickname);
		if (nick == tmpNick)
			return false;
		nick.clear();
	}
	return true;
}

// * ****** Channel Functions ****** * //

Channel*	Server::createChannel(std::string channelName, User* op) {

	Channel*	newChannel = new Channel(channelName, op, this);

	this->_chan_lst.push_back(newChannel);
	return newChannel;
}

void		Server::deleteChannel(Channel *channel) {
	
	std::vector<Channel *>::iterator it = this->_chan_lst.begin();
	std::vector<Channel *>::iterator ite = this->_chan_lst.end();

	for (; it != ite; ++it) {
		if (*it == channel) {
			this->_chan_lst.erase(it);
			break ;
		}
	}
}

// * ****** User functions ****** * //

void	Server::removeUser(User* user) {

	int	fd = user->_socketFd;
	if (this->_user_lst.find(fd) != this->_user_lst.end()) {
		delete this->_user_lst[fd];
		this->_user_lst.erase(fd);
	}
}

std::string		Server::myToUpper(std::string string) {

	std::string				tmpString(string);
	std::string::iterator	it = string.begin();
	std::string::iterator	ite = string.end();

	for (; it != ite; ++it) 
		*it = std::toupper(*it);
	return (tmpString);
}