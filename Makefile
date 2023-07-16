# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/22 13:06:26 by isalama           #+#    #+#              #
#    Updated: 2023/07/15 03:41:41 by tajjid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
USER = $(shell whoami)
CFLAGS = -Wall -Wextra -Werror -g
READLINEFLAG = -lreadline
LIBFT = $(wildcard libft/*.c)
FUNCTIONS = $(wildcard functions/*.c) $(wildcard functions/exec/*.c) \
$(wildcard functions/parsing/commands/*.c) $(wildcard functions/parsing/tokens/*.c) \
$(wildcard functions/parsing/expander/*.c) $(wildcard functions/exec/builtins/*.c) \
$(wildcard functions/parsing/*.c) minishell.c

OBJS = $(FUNCTIONS:.c=.o) $(LIBFT:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS)  -L /Users/$(USER)/.brew/opt/readline/lib -o $(NAME) $(READLINEFLAG)
	@clear

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -I /Users/$(USER)/.brew/opt/readline/include -c $< -o $@
	@clear

clean:
	rm -f $(OBJS)
	@clear

fclean: clean
	rm -f $(NAME)
	@clear

re: fclean all
	@clear
