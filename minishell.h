/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:10:36 by isalama           #+#    #+#             */
/*   Updated: 2023/05/19 03:52:44 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

// TOKENS

enum token_type
{
	WORD,
	SPACE,
	PIPE,
	REDIR,
	DREDIR,
	APPEND,
	HEREDOC,
	SINGLE_QUOTE,
	DOUBLE_QUOTE, 
	DOLLAR,
	EMPTY
};

// STRUCTURES

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
int					ft_strncmp(char *s1, char *s2, int n);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_strdup(const char *s1);
char				*ft_substr(char const *s, int start, size_t len);
char				**ft_split(char const *s, char c);
char				*ft_strjoin(char *s1, char *s2, int flag);
char				*ft_strchr(char *s, int c);
char				*ft_strrchr(const char *s, int c);

// ENVIRONMENT_UTILS
t_env				*ft_envlstnew(char *key, char *value);
void				ft_lstadd_back(t_env **alst, t_env *new);
void				ft_lstclear(t_env **lst);

// TOKENS_FUNCTIONS
t_token				*tokens_creation(char *input, t_env *data);
t_token				*tokens_joiner(t_token *tokens);

// TOKENS_LIST_UTILS
t_token				*ft_t_lstnew(char *content, int type);
t_token				*ft_t_blstlast(t_token *lst);
t_token 			*ft_t_lstlast(t_token *lst);
void				ft_t_lstadd_back(t_token **alst, t_token *new);
void				ft_t_delone(t_token **token);
void				ft_t_lstclear(t_token **lst);

// TOKENS_EXPANSION
t_token				*tokens_expander(t_token *tokens, t_env *data);
char 				*d_quote_expander(char *str, t_env *data);
char 				*word_expander(char *str, t_env *data);
char				*check_expand(char *str, t_env *data);

// EXECUTION
// void				tokens_execution(t_token *tokens, t_env *data);




// FUNCTIONS
void				out_error(char *error_message);
bool				handle_quotes(char *input);

#endif