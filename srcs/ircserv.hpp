#ifndef IRCSERV_HPP
#define IRCSERV_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <map>
#include <netdb.h>
#include <sys/time.h>
#include <sys/select.h>
#include <cstring>
#include <poll.h>
#include <sys/wait.h>
#include <vector>
#include <deque>

#define COLOR_RED		"\x1B[31m"
#define COLOR_GREEN		"\x1B[32m"
#define COLOR_YELLOW	"\x1B[33m"
#define COLOR_RESET		"\033[0m"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE		4096
#endif

#define	ERR_USAGE "usage: ircserv [port] [password]"

#define RPL_WELCOME			"001"
#define RPL_YOURHOST		"002"
#define RPL_CREATED			"003"
#define RPL_MYINFO			"004"

#define RPL_MYINFO_MSG		"<servername> <version> <available user modes> <available channel modes>"

#define CRLF "\r\n"	

#endif