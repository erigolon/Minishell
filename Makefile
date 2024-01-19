# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/24 12:57:38 by vicrodri          #+#    #+#              #
#    Updated: 2024/01/17 22:31:36 by erigolon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

# -lreadline /opt/vagrant/embedded/lib -I /opt/vagrant/embedded/include/readline
# -fsanitize=address

USER		= $(shell whoami)
LIBS		= -L "/Users/$(USER)/.brew/opt/readline/lib" -lreadline
RLHEADER	= -I "/Users/$(USER)/.brew/opt/readline/include"

INC			= libft/
LIBFT		= $(INC)libft.a

SRCDIR		= src
BUILDDIR	= build

SOURCES		= $(wildcard $(SRCDIR)/*.c) $(wildcard $(SRCDIR)/builtins/*.c) $(wildcard $(SRCDIR)/envlst/*.c) \
				$(wildcard $(SRCDIR)/parser/*.c) $(wildcard $(SRCDIR)/executor/*.c) $(wildcard $(SRCDIR)/expander/*.c) \
				$(wildcard $(SRCDIR)/utils/*.c) $(wildcard $(SRCDIR)/wildcard/*.c) 


OBJECTS		= $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@ $(RLHEADER)

all: $(LIBFT)	$(NAME)

$(LIBFT):
	@make -C $(INC)

$(NAME): $(LIBFT) $(OBJECTS) 
	@$(CC) $(CFLAGS) $(LIBFT) $(LIBS) $(OBJECTS) -o $(NAME) 
	@echo "$(GREEN)$(NAME) -> program created! $(DEFAULT)"

clean:
	@rm -rf $(BUILDDIR)
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