/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:10:36 by isalama           #+#    #+#             */
/*   Updated: 2023/05/12 00:07:37 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>


typedef struct t_input_holder
{
	char	*input_command;
	struct t_input_holder *next;
	
} t_input_holder;

typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env *next;
} t_env;


// MESSAGES
# define ERROR_MSG_QUOTE "\033[1;31mError: quotations not closed.\n"

// libft
void				ft_putstr_fd(char *s, int fd);
int					ft_strlen(const char *s);
int					ft_isdigit(int c);
int					ft_strcmp(char *s1, char *s2);
void				ft_lstadd_back(t_input_holder **alst, t_input_holder *new);
t_input_holder		*ft_lstnew(char *input_command);
void				ft_lstclear(t_input_holder **lst);

// functions
void	out_error(char *error_message);
void	handle_quotes(char* input);
char	**ft_split(char const *s, char c);

#endif