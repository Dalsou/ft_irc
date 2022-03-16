# ----------------- #
#     VARIABLES     #
# ----------------- #

NAME	=	ircserv

SRC_LST	=	ircserv.cpp \
			Server.cpp \
			User.cpp \
			Message.cpp \
			Channel.cpp \
			CmdHandler.cpp \
			Command.cpp \
			Cap.cpp \
			Invite.cpp \
			Join.cpp \
			Kick.cpp \
			List.cpp \
			Mode.cpp \
			Names.cpp \
			Nick.cpp \
			Notice.cpp \
			Part.cpp \
			Pass.cpp \
			Ping.cpp \
			PrivMsg.cpp \
			Quit.cpp \
			Topic.cpp \
			UserCmd.cpp 		
			
SRC_DIR	=	$(shell find srcs -type d)
SRCS	=	$(foreach dir, $(SRC_DIR), $(SRC_LST))

OBJ_DIR	=	objs/
OBJS	=	$(addprefix $(OBJ_DIR), $(SRC_LST:%.cpp=%.o))

vpath %.cpp $(foreach dir, $(SRC_DIR)/, $(dir):)

# ----------------- #
#    COMPILATION    #
# ----------------- #

CC		=	clang++

FLAGS	=	-Wall -Wextra -Werror -std=c++98

# ----------------- #
#     FUNCTIONS     #
# ----------------- #

$(OBJ_DIR)%.o: %.cpp
				@mkdir -p $(OBJ_DIR)
				@$(CC) $(FLAGS) -o $@ -c $<

$(NAME):	$(OBJS)
				@$(CC) $(FLAGS) $(OBJS) -o $(NAME)		
				@echo "\n\t\033[36;1m*.............................*"
				@echo "\n\t*    Compilation $(NAME)    *\t   \033[32;1m--------->>> \033[4;5mComplete\033[0m"
				@echo "\n\t\033[036;1m*.............................*\033[0m\n"

all:		$(NAME)

# ----------------- #
#       CLEAN       #
# ----------------- #

RM		=	rm -rf

clean:	
			@$(RM) $(OBJ_DIR)
			@echo "\033[36;1m $(NAME) ------>>  clean\033[0m\n"

fclean:		clean
			@$(RM) $(NAME)
			@echo "\033[36;1m $(NAME) ------>>  fclean\033[0m\n"

re:			fclean all

.PHONY:		all clean fclean re