# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isalama <isalama@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/07 16:19:01 by isalama           #+#    #+#              #
#    Updated: 2023/05/07 16:24:37 by isalama          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT = libft/libft_1.c libft/ft_atoi.c 

SRC_SOURCES = minishell.c

all:
	$(CC) $(CFLAGS) $(LIBFT) $(SRC_SOURCES) -o $(NAME)
	
%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(NAME)

fclean: clean
		