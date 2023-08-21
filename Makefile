# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/24 12:57:38 by vicrodri          #+#    #+#              #
#    Updated: 2023/08/21 15:48:16 by erigolon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

CC	=	gcc

# -lreadline /opt/vagrant/embedded/lib -I /opt/vagrant/embedded/include/readline
CFLAGS	=	-Wall -Wextra -Werror

USER = $(shell whoami)
LIBS = -L "/Users/$(USER)/.brew/opt/readline/lib" -lreadline
RLHEADER = -I "/Users/$(USER)/.brew/opt/readline/include"

INC			= libft/

LIBFT		= $(INC)libft.a

SOURCES	=	$(wildcard src/*.c)	

OBJECTS	=	$(SOURCES:.c=.o)

%.o: %.c
	@$(CC)$(FLAGS) -c $< -o $@ $(RLHEADER)

all: $(LIBFT)	$(NAME)

$(LIBFT):
	@make -C $(INC)

$(NAME): $(LIBFT) $(OBJECTS) 
	@$(CC) $(CFLAGS) $(LIBFT) $(LIBS) $(OBJECTS) -o $(NAME) 
	@echo "$(GREEN)$(NAME) -> program created! $(DEFAULT)"

clean:
	@rm -f $(OBJECTS)
	@make -C $(INC) clean
	@echo "$(YELLOW)$(NAME) -> Object files deleted. "

fclean:	clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) program -> Program and objects files deleted. "

re:	fclean all

.PHONY:	all clean fclean re 

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m