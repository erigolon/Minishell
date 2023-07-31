# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/24 12:57:38 by vicrodri          #+#    #+#              #
#    Updated: 2023/07/31 17:43:36 by vicrodri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

CC	=	gcc

CFLAGS	=	-Wall -Wextra -Werror

INC			= libft/

LIBFT		= $(INC)libft.a

SOURCES	=	$(wildcard src/*.c)	

OBJECTS	=	$(SOURCES:.c=.o)

%.o: %.c
	@$(CC)$(FLAGS) -c $< -o $@

all: $(LIBFT)	$(NAME)

$(LIBFT):
	@make -C $(INC)

$(NAME)		: $(LIBFT) $(OBJECTS) 
	@$(CC) $(CFLAGS) $(LIBFT) $(OBJECTS) -lreadline -o $(NAME)
			@echo "$(GREEN)$(NAME) -> program created! $(DEFAULT)"

clean:
		rm -f $(OBJECTS)
		@make -C $(INC) clean
		@echo "$(YELLOW)$(NAME) -> Object files deleted. "

fclean:	clean
		rm -f $(NAME)
		@echo "$(RED)$(NAME) program -> Program and objects files deleted. "

re:	fclean all

.PHONY:	all clean fclean re 

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m