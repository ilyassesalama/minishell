# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isalama <isalama@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/22 13:06:26 by isalama           #+#    #+#              #
#    Updated: 2023/07/26 17:50:22 by isalama          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
USER = $(shell whoami)
CFLAGS = -Wall -Wextra -Werror
READLINEFLAG = -lreadline
LIBFT = \
libft/ft_atoi.c \
libft/ft_itoa.c \
libft/ft_putnbr_fd.c \
libft/ft_split.c \
libft/ft_substr.c \
libft/libft_1.c \
libft/libft_2.c \
libft/libft_3.c \
libft/libft_4.c
FUNCTIONS = \
functions/exec/builtins/builtins_1.c \
functions/exec/builtins/builtins_2.c \
functions/exec/builtins/builtins_exec.c \
functions/exec/builtins/builtins_utils.c \
functions/exec/builtins/export_1.c \
functions/exec/builtins/export_2.c \
functions/exec/env_utils.c \
functions/exec/exec_utils.c \
functions/exec/exec_utils_2.c \
functions/exec/exec_utils_3.c \
functions/exec/signals.c \
functions/exec/tokens_execution.c \
functions/parsing/commands/commands_creator.c \
functions/parsing/commands/commands_f_opener.c \
functions/parsing/commands/commands_filler.c \
functions/parsing/commands/commands_utils.c \
functions/parsing/commands/herdoc_handler.c \
functions/parsing/errors_handlers_1.c \
functions/parsing/expander/expanders.c \
functions/parsing/expander/expanders_utils_1.c \
functions/parsing/expander/tokens_joiner.c \
functions/parsing/signals.c \
functions/parsing/tokens/tokens_creator.c \
functions/parsing/tokens/tokens_utils.c \
functions/parsing/tokens/tokens_utils_1.c \
minishell.c

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
