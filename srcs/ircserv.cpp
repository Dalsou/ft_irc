#include "ircserv.hpp"
#include "Server/Server.hpp"

static void	handleSignal(int signum) {
	if (signum == SIGINT || signum == SIGQUIT)
		std::cout << COLOR_GREEN << "\b\bServer stopped. Good bye!\n" << COLOR_RESET;
	exit(0);
}

static int	checkArgs(int ac, char** av, int* port, std::string* password) {
	
	if (ac != 3) {
		std::cout << COLOR_RED << ERR_USAGE << COLOR_RESET << std::endl;
		return 1;
	}

	*(port) = std::atoi(av[1]);
	if (*port <= 0 || *port > 0xffff) {
		std::cout << COLOR_RED << "Invalid port number\n" << COLOR_RESET;
		return 1;
	}
	*password = av[2];

	return 0;
}

int main(int ac, char** av) {

	int			port;
	std::string	password;

	signal(SIGINT, handleSignal);
	signal(SIGQUIT, handleSignal);

	if (checkArgs(ac, av, &port, &password))
		return (EXIT_FAILURE);

	Server server(av[0], port, password);
	if (server.setUp())
		return (EXIT_FAILURE);
	if (server.start())
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}