# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avolcy <avolcy@student.42barcelon>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/07 18:37:10 by avolcy            #+#    #+#              #
#    Updated: 2023/09/30 22:04:02 by avolcy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
RM = rm -rf
CFLAGS = -MMD -Wall -Werror -Wextra
HEADER = minitalk.h

#=============|   PATHS   |================#
LIB_NAME = libft.a
LIB_DIR = ./libft/
INCLUDE_LIB = -L $(LIB_DIR) -lft
#__________________________________________#


#============| MANDATORY |==================#
CLIENT_NAME = client
SERVER_NAME = server

CLIENT_SRC = srcs/client.c
SERVER_SRC = srcs/server.c

CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SERVER_OBJ = $(SERVER_SRC:.c=.o)

CLIENT_DEPS = $(CLIENT_OBJ:.o=.d)
SERVER_DEPS = $(SERVER_OBJ:.o=.d)

all:
	$(MAKE) -C $(LIB_DIR)
	$(MAKE) $(SERVER_NAME)
	$(MAKE) $(CLIENT_NAME)	

$(SERVER_NAME):	$(SERVER_OBJ) $(LIB_DIR)$(LIB_NAME)
	$(CC) $(CFLAGS) $(SERVER_OBJ) $(INCLUDE_LIB) -o $@
	@$(MSG_OK_SERVER)

$(CLIENT_NAME):	$(CLIENT_OBJ) $(LIB_DIR)$(LIB_NAME)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) $(INCLUDE_LIB) -o $@
	@$(MSG_OK_CLIENT)
#_____________________________________________________________#


#=============|  BONUS  |==================#
B_CLIENT_NAME = client_bonus
B_SERVER_NAME = server_bonus

B_CLIENT_SRC = srcs_bonus/client_bonus.c
B_SERVER_SRC = srcs_bonus/server_bonus.c

B_CLIENT_OBJ = $(B_CLIENT_SRC:.c=.o)
B_SERVER_OBJ = $(B_SERVER_SRC:.c=.o)

B_CLIENT_DEPS = $(B_CLIENT_OBJ:.o=.d)
B_SERVER_DEPS = $(B_SERVER_OBJ:.o=.d)

bonus:
	$(MAKE) -C $(LIB_DIR)
	$(MAKE) $(B_SERVER_NAME)
	$(MAKE) $(B_CLIENT_NAME)	

$(B_SERVER_NAME): $(B_SERVER_OBJ) $(LIB_DIR)$(LIB_NAME)
	$(CC) $(CFLAGS) $(B_SERVER_OBJ) $(INCLUDE_LIB) -o $@
	@$(MSG_OK_B_SERVER)

$(B_CLIENT_NAME): $(B_CLIENT_OBJ) $(LIB_DIR)$(LIB_NAME)
	$(CC) $(CFLAGS) $(B_CLIENT_OBJ) $(INCLUDE_LIB) -o $@
	@$(MSG_OK_B_CLIENT)
#__________________________________________________________#

#=================| BUIDING OBJ_FILES |===================================#
%.o: %.c
	$(CC) $(CFLAGS) -I $(LIB_DIR) -c $< -o $@

-include $(SERVER_DEPS) $(CLIENT_DEPS) $(B_SERVER_DEPS) $(B_CLIENT_DEPS)
#______________________________________________________________________#

#=============| CLEANING_RULES |=====================================#
clean:
	$(RM) $(SERVER_OBJ) $(SERVER_DEPS) $(CLIENT_OBJ) $(CLIENT_DEPS)
	$(RM) $(B_SERVER_OBJ) $(B_SERVER_DEPS) $(B_CLIENT_OBJ) $(B_CLIENT_DEPS)
	$(MAKE) clean -C $(LIB_DIR)
	@$(MSG_OK_CLEAN)

fclean:	clean
	$(RM) $(SERVER_NAME) $(CLIENT_NAME) 
	$(RM) $(B_SERVER_NAME) $(B_CLIENT_NAME)
	@$(MAKE) fclean -C $(LIB_DIR)
	@$(MSG_OK_FCLEAN)

		
re:			fclean all

rebonus:	fclean bonus
#____________________________________________________________________#

OBJS_DEPS_LST = $(shell find . -maxdepth 2 -name '*.o' -o -name '*.d')
EXECUTS_LST = $(shell find . -maxdepth 2 -name $(SERVER_NAME) \
			  -o -name $(CLIENT_NAME) -o -name $(B_SERVER_NAME) \
			  -o -name $(B_CLIENT_NAME) -o -name $(LIB_NAME))
#_____________________________________________________________________#

#==============| COLORS |========================#
YELLOW 			= 	\033[0;93m
BOLD_YELLOW		=	\033[1;33m
DEF_COLOR		=	\033[0m
#________________________________________________#

#===============| MESSAGES |=========================== #
MSG_OK_SERVER = @echo "$(BOLD_YELLOW)Server executable compiled$(DEF_COLOR)"
MSG_OK_CLIENT =	@echo "$(BOLD_YELLOW)Client executable compiled$(DEF_COLOR)"
MSG_OK_B_SERVER = @echo "$(BOLD_YELLOW)Server bonus executable compiled$(DEF_COLOR)"
MSG_OK_B_CLIENT	= @echo "$(BOLD_YELLOW)Client bonus executable compiled$(DEF_COLOR)"
MSG_OK_CLEAN = @echo "$(BOLD_YELLOW)Object and dependency files removed$(DEF_COLOR)"
MSG_NO_CLEAN = @echo "$(BOLD_YELLOW)No object or dependency files to remove$(DEF_COLOR)"
MSG_OK_FCLEAN = @echo "$(BOLD_YELLOW)Executable files removed$(DEF_COLOR)"
MSG_NO_FCLEAN = @echo "$(BOLD_YELLOW)No executable files found to remove$(DEF_COLOR)"
#____________________________________________________________________________________#

#------------------------------------#
.PHONY:	all clean fclean re rebonus
#-----------------------------------#
