# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isalama <isalama@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 16:19:01 by isalama           #+#    #+#              #
#    Updated: 2023/05/11 20:56:13 by isalama          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
READLINEFLAG = -lreadline
LIBFT = libft/libft_1.c libft/ft_atoi.c 

SRC_SOURCES = minishell.c

all:
	$(CC) $(CFLAGS) $(READLINEFLAG) $(LIBFT) $(SRC_SOURCES) -o $(NAME)
	@clear
%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@
	@clear
clean:
	rm -f $(NAME)
	@clear
fclean: clean
		