/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_initiator.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 22:51:22 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/16 23:17:43 by tajjid           ###   ########.fr       */
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

bool	heredoc_expand_checker(t_token **tmp_tokens,
		bool expand, char **limiter)
{
	if ((*tmp_tokens)-> next -> type != SPACER)
	{
		if ((*tmp_tokens)-> next -> type == WORD
			|| (*tmp_tokens)-> next -> type == DOLLAR)
			expand = true;
		else
			expand = false;
		*limiter = ft_strdup((*tmp_tokens)-> next -> content);
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
		*limiter = ft_strdup((*tmp_tokens)-> next -> next -> content);
		(*tmp_tokens)-> type = NONUSABLE;
		(*tmp_tokens)-> next -> type = NONUSABLE;
		(*tmp_tokens)-> next -> next -> type = NONUSABLE;
	}
	return (expand);
}

int	heredoc_handler(t_token **tmp_tokens, int input,
			int output, t_env *env)
{
	bool	expand;
	char	*limiter;

	herdoc_signal();
	expand = false;
	limiter = NULL;
	expand = heredoc_expand_checker(tmp_tokens, expand, &limiter);
	printf("limiter = %s\n", limiter);
	output = fd_opener("/tmp/tmp.txt", 0);
	heredoc_readline(output, limiter, env, expand);
	input = fd_opener("/tmp/tmp.txt", 2);
	return (input);
}
