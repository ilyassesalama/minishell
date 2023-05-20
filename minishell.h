/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:44:36 by tajjid            #+#    #+#             */
/*   Updated: 2023/05/20 05:27:20 by tajjid           ###   ########.fr       */
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
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

// TOKENS

enum e_token_type
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
	char				*content;
	int					type;
	struct s_token		*next;
}	t_token;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}	t_env;

typedef struct s_command
{
	char				*command;
	char				**args;
	int					output;
	int					input;
	struct s_command	*next;
}	t_command;

// MESSAGES
# define ERROR_MSG_QUOTE "\033[1;31mError: quotations not closed.\n"
# define ERROR_MSG_ENV "\033[1;31mError: HOME not set.\n"
# define ERROR_MSG_INV_PATH "\033[1;31mNo such file or directory.\n"
# define ERROR_MSG_SYNTAX "\033[1;31mError: syntax error.\n"

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
char				*ft_strrchr(char *s, int c);

// ENVIRONMENT_UTILS
t_env				*ft_envlstnew(char *key, char *value);
void				ft_lstadd_back(t_env **alst, t_env *new);
void				ft_lstclear(t_env **lst);

// TOKENS_FUNCTIONS
t_token				*tokens_creation(char *input, t_env *data);
t_token				*tokens_joiner(t_token *tokens);
t_token				*ft_t_lstnew(char *content, int type);
t_token				*ft_t_blstlast(t_token *lst);
t_token				*ft_t_lstlast(t_token *lst);
void				ft_t_lstadd_back(t_token **alst, t_token *new);
 t_token			*ft_t_spaces_deleter(t_token *tokens);
void				ft_t_lstclear(t_token **lst);

// TOKENS_EXPANSION
t_token				*tokens_expander(t_token *tokens, t_env *data);
char				*d_quote_expander(char *str, t_env *data);
char				*word_expander(char *str, t_env *data);
char				*check_expand(char *str, t_env *data);

// EXECUTION_FUNCTIONS
void				tokens_execution(t_env *env);

// --> EXECUTION_FUNCTIONS --> BUILT_INS
void				lets_pwd(void);
void				lets_echo(t_command *commands);
void				lets_cd(t_command *commands, t_env *env);
void				lets_exit(void);
void				lets_env(t_env *env);
void				lets_export(t_env *env, char **args);
void				lets_unset(t_env **env, char **args);

// --> EXECUTION_FUNCTIONS --> TESTING
t_command			*command_lstnew(char *command, char **args, int input, int output);
void				command_add_back(t_command **alst, t_command *new);

// COMMANDS CREATION
t_command			*command_creator(t_token *tokens);
t_command			*ft_c_lstnew(char *command, int output, int input);
void				ft_c_lstadd_back(t_command **list, t_command *new);
void				ft_c_lstclear(t_command **list);
int					fd_opener(char *file, int mode);

// ERROR HANDLERS
void				out_error(char *error_message);
bool				syntax_error(t_token *tokens);
bool				handle_quotes(char *input);

// UTILS
char				*get_current_dir(char *path);
char				*get_env_value(char *key, t_env *env);

#endif