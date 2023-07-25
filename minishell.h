/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:15:22 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/25 18:29:45 by isalama          ###   ########.fr       */
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
# include <errno.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

// TOKENS

enum e_token_type
{
	WORD,
	SPACER,
	PIPE,
	OUT_REDIR,
	IN_REDIR,
	APPEND,
	HEREDOC,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	DOLLAR,
	EMPTY,
	NONUSABLE
};

// STRUCTURES

typedef struct s_global {
	int		exit_status;
	int		heredoc_eof;
	char	*home;
}	t_global;

t_global	g_global;

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
	bool				is_hidden;
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

typedef struct s_cmdtls
{
	int					input;
	int					output;
	int					flag;
	int					no_file;
	char				**args;
	t_token				*tmp_tokens2;
	t_command			*commands;
}	t_cmdtls;

// MESSAGES
# define ERROR_MSG "\001\033[1;31m\002Error: \001\033[0m\002"
# define ERROR_MSG_QUOTE "\001\033[1;31m\002Error: quotations not closed. \
\n\001\033[0m\002"
# define ERROR_MSG_ENV "\001\033[1;31m\002Error: HOME not set. \
\n\001\033[0m\002"
# define ERROR_MSG_INV_PATH "\001\033[1;31m\002Error: no such file or directory \
\n\001\033[0m\002"
# define ERROR_MSG_SYNTAX "\001\033[1;31m\002Error: syntax error. \
\n\001\033[0m\002"
# define ERROR_MSG_IDENTIFIER "\001\033[1;31m\002Error: not a valid identifier. \
\n\001\033[0m\002"
# define ERROR_MSG_CD_ERR "\001\033[1;31m\002Error: cd: error retrieving current directory: getcwd: \
cannot access parent directories: No such file or directory.\n\001\033[0m\002"
# define ERROR_MSG_CMD_404 "\001\033[1;31m\002Error: command not found: \
\001\033[0m\002"
# define ERROR_PIPE "\001\033[1;31m\002Error: minishell: pipe: \
Resource temporarily unavailable. Also, wtf is this test?\n\001\033[0m\002"
# define ERROR_FORK "\001\033[1;31m\002Error: minishell: fork: \
Resource temporarily unavailable. Also, wtf is this test?\n\001\033[0m\002"

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
char				*ft_substr(char *s, int start, size_t len);
char				**ft_split(char const *s, char c);
char				*ft_strjoin(char *s1, char *s2, int flag);
char				*ft_strchr(char *s, int c);
char				*ft_strrchr(char *s, int c);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr_fd(int n, int fd);
bool				is_alpha(char c);
bool				is_digit(char c);
bool				ft_istrdigit(char *str);
bool				ft_istrnegdigit(char *str);
int					ft_atoi(char *str);
char				*ft_itoa(int n);

// ENVIRONMENT_UTILS
t_env				*ft_envlstnew(char *key, char *value);
void				ft_lstadd_back(t_env **alst, t_env *new);
void				ft_e_lstclear(t_env **env_lst);
void				ft_free_array(char **array);

// TOKENS_FUNCTIONS
t_token				*tokens_creation(char *input, t_env *data);
t_token				*tokens_checker(char *input, t_env *data);
t_token				*tokens_joiner(t_token *tokens);
t_token				*handle_space(char *input, int *i, t_token *tokens);
t_token				*handle_singlequote(char *input, int *i, t_token *tokens);
t_token				*handle_doublequote(char *input, int *i, t_token *tokens);
t_token				*handle_special(char *input, int *i, t_token *tokens);
t_token				*handle_dollar(char *input, int *i, t_token *tokens);
t_token				*handle_word(char *input, int *i, t_token *tokens);

// TOKENS_FUNCTIONS --> UTILS
t_token				*ft_t_lstnew(char *content, int type);
t_token				*ft_t_lstlast(t_token *lst, int type);
void				ft_t_lstadd_back(t_token **alst, t_token *new);
t_token				*ft_t_spaces_deleter(t_token *tokens);
void				ft_t_lstclear(t_token **token_lst);
void				content_joiner(t_token **tmp, t_token *tokes, int type);
bool				join_checker(int type);
// TOKENS_FUNCTIONS --> SIGNALS
void				herdoc_signal(void);

// TOKENS_EXPANSION
t_token				*tokens_expander(t_token *tokens, t_env *data);
char				*d_quote_expander(char *str, t_env *data);
char				*word_expander(char *str, t_env *data);
char				*chack_expand1(int *i, char *str, char *tmp, t_env *data);
char				*chack_expand2(int *i, char *str, char *tmp);
char				*d_expander(char *str, t_env *data);
void				expand_token_checker(t_env *data, t_token **tmp);
void				dollar_joiner(t_token **tmp, t_token *tokens);
void				token_join_checker(t_token **tmp, t_token *tokens);

// EXECUTION_FUNCTIONS
void				tokens_execution(t_command *commands, t_env **env);
void				builtin_execution(t_command *commands, t_env **env);
void				close_resources(t_command *commands, int *pipex);

// EXECUTION_FUNCTIONS --> UTILS
char				**env_to_array(t_env *env);
bool				is_non_dir(t_command **commands);
char				*get_function_path(char *content, t_env *env);

// EXECUTION_FUNCTIONS --> BUILT_INS
int					lets_pwd(t_env *env, int fd);
int					lets_echo(t_command *commands);
int					lets_cd(t_command *commands, t_env *env);
void				lets_exit(t_command *commands);
int					lets_env(t_env *env, int fd);
void				lets_export(t_env **env, char **args);
void				lets_unset(t_env **env, char **args);

// EXECUTION_FUNCTIONS --> BUILT_INS --> UTILS
bool				is_builtin(t_command *commands);
void				export_new(t_env **env, int index, char *identifier,
						bool is_equal);
void				export_append(t_env **env, int plus_pos, char *ident);
bool				is_exportable(char *identifier);

// EXECUTION_FUNCTIONS --> TESTING
t_command			*command_lstnew(char *command, char **args, int input,
						int output);
void				command_add_back(t_command **alst, t_command *new);
int					command_lst_size(t_command *cmd);

// EXECUTION_FUNCTIONS --> SIGNALS
void				signals_handler(void);
void				invalidate_signals(void);

// COMMANDS UTILS
char				**args_filler(char **args, char *token);
int					command_filler_2(t_token **tokens,
						char **command, char ***args);
t_command			*command_filler(t_token *tokens,
						t_command *com, int in, int out);

// COMMANDS CREATION
t_command			*command_creator(t_token *tokens, t_env *env);
t_command			*ft_c_lstnew(char *command, char **args, int input,
						int output);
void				ft_c_lstadd_back(t_command **list, t_command *new);
void				ft_c_lstclear(t_command **list);

// COMMANDS CREATION --> INITIALIZATION
void				heredoc_readline(int output, char *limiter,
						t_env *env, int expand);
bool				heredoc_expand_checker(t_token **tmp_tokens,
						bool expand, char **limiter, char *tmp_file);
void				heredoc_handler(t_token **tmp_tokens,
						int output, t_env *env);
void				token_type_handler(t_token **tokens, t_env *env,
						int *input, int *output);
t_command			*command_filler_handler(t_token *tokens,
						t_command *commands, t_token **tmp_tokens, int *flag);

// COMMANDS OPNER
void				files_opener(t_token **tmp_tokens, int type, int *output);
void				dredir_opener(t_token **tmp_tokens, int type, int *input);
bool				files_if_checker(t_token *tmp_tokens);
int					fd_opener(char *file, int mode);

// ERROR HANDLERS
void				out_error(char *error_message);
bool				syntax_error(t_token *tokens);
bool				handle_quotes(char *input);

// UTILS
char				*get_current_path(t_env *env);
void				update_env(char *key, char *value, t_env *env);
char				*get_env_value(char *key, t_env *env);

#endif