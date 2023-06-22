# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 16:19:01 by isalama           #+#    #+#              #
#    Updated: 2023/06/22 12:17:52 by tajjid           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
READLINEFLAG = -lreadline
LIBFT = $(wildcard libft/*.c)
FUNCTIONS = $(wildcard functions/*.c) $(wildcard functions/exec/*.c) $(wildcard functions/parsing/*.c) $(wildcard functions/exec/builtins/*.c) 

all:
	$(CC) $(CFLAGS) $(READLINEFLAG) $(LIBFT) $(FUNCTIONS) minishell.c -o $(NAME)
	@clear
%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@
	@clear
clean:
	rm -f $(NAME)
	@clear
fclean: clean

re: fclean all
	@clear