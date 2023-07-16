/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_creator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 04:43:28 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/15 23:24:59 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	**args_filler(char **args, char *token)
{
	char	**tmp2d;
	int		i;

	i = 0;
	if (!args)
	{
		tmp2d = malloc(sizeof(char *) * 2);
		tmp2d[0] = ft_strdup(token);
		tmp2d[1] = NULL;
		return (tmp2d);
	}
	while (args[i])
		i++;
	tmp2d = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (args[i])
	{
		tmp2d[i] = ft_strdup(args[i]);
		i++;
	}
	tmp2d[i] = ft_strdup(token);
	tmp2d[i + 1] = NULL;
	return (tmp2d);
}

t_command	*command_filler(t_token *tokens, t_command *com, int in, int out)
{
	t_command	*tmp;
	char		*command;
	char		**args;

	args = NULL;
	command = NULL;
	if (tokens -> type == NONUSABLE || tokens -> type == SPACER)
	{
		while (tokens && (tokens -> type == NONUSABLE || tokens -> type == SPACER))
			tokens = tokens -> next;
	}
	if (tokens && tokens -> type == WORD)
	{
		args = ft_split(tokens -> content, ' ');
		command = ft_strdup(args[0]);
		if (!command)
		{
			free(command);
			command = ft_strdup("");
		}
		tokens = tokens -> next;
	}
	else if (tokens && (tokens -> type == DOUBLE_QUOTE || tokens -> type == SINGLE_QUOTE))
	{
		command = ft_strdup(tokens -> content);
		args = args_filler(args, tokens -> content);
		tokens = tokens -> next;
	}
	else if (!tokens)
	{
		command = ft_strdup("");
		args = malloc(sizeof(char *) * 1);
		args[0] = NULL;
	}
	while (tokens && tokens -> type != PIPE)
	{
		if (tokens -> type == SPACER || tokens -> type == NONUSABLE)
			tokens = tokens -> next;
		else
		{
			args = args_filler(args, tokens -> content);
			tokens = tokens -> next;
		}
	}
	tmp = ft_c_lstnew(command, args, in, out);
	ft_c_lstadd_back(&com, tmp);
	return (com);
}

static void	heredoc_sigint(int sigint)
{
	if (sigint != SIGINT)
		return ;
	if (g_global.heredoc_eof == 1)
	{
		g_global.heredoc_eof = 0;
		return ;
	}
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	g_global.heredoc_eof = 1;
}

void	herdoc_signal(void)
{
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}

t_command	*command_creator(t_token *tokens, t_env *env)
{
	t_token		*tmp_tokens;
	t_token		*tmp_tokens2;
	t_command	*commands;
	t_command	*tmp;
	char 		*line;
	char		*limiter;
	int			input;
	int			output;
	int 		flag;
	bool 		expand;
	
	tmp_tokens = tokens;
	tmp_tokens2 = tokens;
	commands = NULL;
	tmp = NULL;
	line = NULL;
	input = 0;
	output = 1;
	flag = 0;

	while (tmp_tokens)
	{
		if (flag == 1)
		{
			tmp_tokens2 = tmp_tokens;
			flag = 0;
		}
		if (tmp_tokens -> type == PIPE)
		{
			commands = command_filler(tmp_tokens2, commands, input, output);
			input = 0;
			output = 1;
			flag = 1;
			if (tmp_tokens -> next -> type == SPACER)
				tmp_tokens = tmp_tokens -> next;
		}
		if (tmp_tokens -> type == HEREDOC)
		{
			herdoc_signal();
			output = fd_opener("/tmp/tmp.txt", 1);
			if (tmp_tokens -> next -> type != SPACER)
			{
				if (tmp_tokens -> next -> type == WORD 
						|| tmp_tokens -> next -> type == DOLLAR)
					expand = true;
				else
					expand = false;
				limiter = ft_strdup(tmp_tokens -> next -> content);
				tmp_tokens -> type = NONUSABLE;
				tmp_tokens -> next -> type = NONUSABLE;
			}
			else
			{
				if (tmp_tokens -> next -> next -> type == WORD 
						|| tmp_tokens -> next -> next -> type == DOLLAR)
					expand = true;
				else
					expand = false;
				limiter = ft_strdup(tmp_tokens -> next -> next -> content);
				tmp_tokens -> type = NONUSABLE;
				tmp_tokens -> next -> type = NONUSABLE;
				tmp_tokens -> next -> next -> type = NONUSABLE;
			}
			while (1 && g_global.heredoc_eof == 0)
			{
				line = readline("> ");
				if(!line || g_global.heredoc_eof == 1 || ft_strcmp(line, limiter) == 0)
				{
					break ;
				}
				if (expand)
				{
					while(line && ft_strchr(line, '$'))
						line = d_quote_expander(line, env);
				}
				write(output, line, ft_strlen(line));
				write(output, "\n", 1);
				free(line);
			}	
			if (line && g_global.heredoc_eof == 0)
				free(line);
			close(output);
			input = fd_opener("/tmp/tmp.txt", 3);
			output = 1;
		}
		else if (tmp_tokens -> type == APPEND)
		{
			if (tmp_tokens -> next -> type == WORD || tmp_tokens -> next -> type == SINGLE_QUOTE || tmp_tokens -> next -> type == DOUBLE_QUOTE)
			{
				if (output != 1)
					close(output);
				output = fd_opener(tmp_tokens -> next->content, 2);
				tmp_tokens -> type = NONUSABLE;
				tmp_tokens -> next -> type = NONUSABLE;
				tmp_tokens = tmp_tokens -> next;
			}
			else if ((tmp_tokens -> next -> type == SPACER && tmp_tokens -> next -> next -> type == WORD)
				|| (tmp_tokens -> next -> type == SPACER && tmp_tokens -> next -> next -> type == SINGLE_QUOTE)
				|| (tmp_tokens -> next -> type == SPACER && tmp_tokens -> next -> next -> type == DOUBLE_QUOTE))
			{
				if (output != 1)
					close(output);
				output = fd_opener(tmp_tokens -> next -> next -> content, 2);
				tmp_tokens -> type = NONUSABLE;
				tmp_tokens -> next -> type = NONUSABLE;
				tmp_tokens -> next -> next -> type = NONUSABLE;
				tmp_tokens = tmp_tokens -> next -> next;
			}
		}
		else if (tmp_tokens -> type == REDIR)
		{
			if (tmp_tokens -> next -> type == WORD || tmp_tokens -> next -> type == SINGLE_QUOTE || tmp_tokens -> next -> type == DOUBLE_QUOTE)
			{
				if (output != 1)
					close(output);
				output = fd_opener(tmp_tokens -> next->content, 1);
				tmp_tokens -> type = NONUSABLE;
				tmp_tokens -> next -> type = NONUSABLE;
				tmp_tokens = tmp_tokens -> next;
			}
			else if ((tmp_tokens -> next -> type == SPACER && tmp_tokens -> next -> next -> type == WORD)
				|| (tmp_tokens -> next -> type == SPACER && tmp_tokens -> next -> next -> type == SINGLE_QUOTE)
				|| (tmp_tokens -> next -> type == SPACER && tmp_tokens -> next -> next -> type == DOUBLE_QUOTE))
			{
				if (output != 1)
					close(output);
				output = fd_opener(tmp_tokens -> next -> next->content, 1);
				tmp_tokens -> type = NONUSABLE;
				tmp_tokens -> next -> type = NONUSABLE;
				tmp_tokens -> next -> next -> type = NONUSABLE;
				tmp_tokens = tmp_tokens -> next -> next;
			}
		}
		else if (tmp_tokens -> type == DREDIR)
		{
			if (tmp_tokens -> next -> type == WORD || tmp_tokens -> next -> type == SINGLE_QUOTE || tmp_tokens -> next -> type == DOUBLE_QUOTE)
			{
				if (input != 0)
					close(input);
				input = fd_opener(tmp_tokens -> next->content, 3);
				tmp_tokens -> type = NONUSABLE;
				tmp_tokens -> next -> type = NONUSABLE;
				tmp_tokens = tmp_tokens -> next;
			}
			else if ((tmp_tokens -> next -> type == SPACER && tmp_tokens -> next -> next -> type == WORD)
				|| (tmp_tokens -> next -> type == SPACER && tmp_tokens -> next -> next -> type == SINGLE_QUOTE)
				|| (tmp_tokens -> next -> type == SPACER && tmp_tokens -> next -> next -> type == DOUBLE_QUOTE))
			{
				if (input != 0)
					close(input);
				input = fd_opener(tmp_tokens -> next -> next->content, 3);
				tmp_tokens -> type = NONUSABLE;
				tmp_tokens -> next -> type = NONUSABLE;
				tmp_tokens -> next -> next -> type = NONUSABLE;
				tmp_tokens = tmp_tokens -> next -> next;
			}
		}
		tmp_tokens = tmp_tokens -> next;
	}
 	commands = command_filler(tmp_tokens2, commands, input, output);
	return (commands);
}