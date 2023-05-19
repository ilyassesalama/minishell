# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isalama <isalama@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 16:19:01 by isalama           #+#    #+#              #
#    Updated: 2023/05/19 19:40:25 by isalama          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
READLINEFLAG = -lreadline
LIBFT = $(wildcard libft/*.c)
FUNCTIONS = $(wildcard functions/*.c) $(wildcard functions/exec/*.c)

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
		