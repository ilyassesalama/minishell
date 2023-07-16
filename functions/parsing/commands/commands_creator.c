/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_creator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 04:43:28 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/16 20:39:20 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	heredoc_readline(int output, char *limiter, t_env *env, int expand)
{
	char	*line;

	line = NULL;
	while (1 && g_global.heredoc_eof == 0)
	{
		line = readline("> ");
		if (!line || g_global.heredoc_eof == 1 || ft_strcmp(line, limiter) == 0)
			break ;
		if (expand)
		{
			while (line && ft_strchr(line, '$'))
				line = d_quote_expander(line, env);
		}
		write(output, line, ft_strlen(line));
		write(output, "\n", 1);
		free(line);
	}
	if (line && g_global.heredoc_eof == 0)
		free(line);
	close(output);
}

void	heredoc_handler(t_token **tmp_tokens, int *input,
			int *output, t_env *env)
{
	bool	expand;
	char	*limiter;

	herdoc_signal();
	*output = fd_opener("/tmp/tmp.txt", 1);
	if ((*tmp_tokens)-> next -> type != SPACER)
	{
		if ((*tmp_tokens)-> next -> type == WORD
			|| (*tmp_tokens)-> next -> type == DOLLAR)
			expand = true;
		else
			expand = false;
		limiter = ft_strdup((*tmp_tokens)-> next -> content);
		(*tmp_tokens)-> type = NONUSABLE;
		(*tmp_tokens)-> next -> type = NONUSABLE;
	}
	else
	{
		if ((*tmp_tokens)-> next -> next -> type == WORD
			|| (*tmp_tokens)-> next -> next -> type == DOLLAR)
			expand = true;
		else
			expand = false;
		limiter = ft_strdup((*tmp_tokens)-> next -> next -> content);
		(*tmp_tokens)-> type = NONUSABLE;
		(*tmp_tokens)-> next -> type = NONUSABLE;
		(*tmp_tokens)-> next -> next -> type = NONUSABLE;
	}
	heredoc_readline(*output, limiter, env, expand);
	*output = 1;
	*input = fd_opener("/tmp/tmp.txt", 3);
}


t_command	*command_creator(t_token *tokens, t_env *env)
{
	t_token		*tmp_tokens;
	t_token		*tmp_tokens2;
	t_command	*commands;
	t_command	*tmp;
	
	int			input;
	int			output;
	int 		flag;
	
	tmp_tokens = tokens;
	tmp_tokens2 = tokens;
	commands = NULL;
	tmp = NULL;
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
			heredoc_handler(&tmp_tokens, &input, &output, env);
		}
		else if (tmp_tokens -> type == APPEND || tmp_tokens -> type == REDIR)
			files_opener(&tmp_tokens, tmp_tokens -> type, &output);
		else if (tmp_tokens -> type == DREDIR)
			dredir_opener(&tmp_tokens, tmp_tokens -> type, &input);
		tmp_tokens = tmp_tokens -> next;
	}
 	commands = command_filler(tmp_tokens2, commands, input, output);
	return (commands);
}
