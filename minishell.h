/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:10:36 by isalama           #+#    #+#             */
/*   Updated: 2023/05/12 22:07:24 by tajjid           ###   ########.fr       */
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

// TOKENS
# define WORD 1
# define SPACE 2
# define PIPE 3
# define REDIR 4
# define DREDIR 5
# define APPEND 6
# define HEREDOC 7
# define SINGLE_QUOTE 8
# define DOUBLE_QUOTE 9

// STRUCTURES
typedef struct s_data
{
	char			*env_path;
	struct s_data	*next;
}	t_data;

typedef struct s_token
{
	char			*content;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;


// MESSAGES
# define ERROR_MSG_QUOTE "\033[1;31mError: quotations not closed.\n"

// LIBFT
void				ft_putstr_fd(char *s, int fd);
int					ft_strlen(const char *s);
int					ft_isdigit(int c);
int					ft_strcmp(char *s1, char *s2);
void				ft_lstadd_back(t_data **alst, t_data *new);
t_data				*ft_lstnew(char *input_command);
void				ft_lstclear(t_data **lst);
void				*ft_calloc(size_t count, size_t size);
void				ft_bzero(void *s, size_t n);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_strdup(const char *s1);
char				*ft_substr(char const *s, int start, size_t len);
char				**ft_split(char const *s, char c);
char				*ft_strjoin(char *s1, char *s2, int flag);
char				*ft_strchr(char *s, int c);

// TOKENS_FUNCTIONS
t_token				*tokens_creation(char *input);
void				tokens_execution(t_token *tokens, t_data *data);
t_token				*ft_t_lstnew(char *content, int type);
void				ft_t_lstadd_back(t_token **alst, t_token *new);
void				ft_t_lstclear(t_token **lst);

// FUNCTIONS
void				out_error(char *error_message);
bool				handle_quotes(char *input);

#endif