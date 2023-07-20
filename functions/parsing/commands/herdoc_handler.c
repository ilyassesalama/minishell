/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 22:51:22 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/20 16:58:21 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	heredoc_readline(int output, char *limiter, t_env *env, int expand)
{
	char	*line;
	char	*tmp;

	(void)env;
	(void)expand;
	tmp = NULL;
	line = NULL;
	while (1 && g_global.heredoc_eof == 0)
	{
		line = readline("> ");
		if (!line || g_global.heredoc_eof == 1 || ft_strcmp(line, limiter) == 0)
			break ;
		if (expand)
		{
			tmp = line;
			line = d_quote_expander(tmp, env);
			free(tmp);
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
		bool expand, char **limiter, char *tmp_file)
{
	t_token	*tmp;

	tmp = *tmp_tokens;
	(*tmp_tokens)-> type = IN_REDIR;
	(*tmp_tokens) = (*tmp_tokens)-> next;
	if ((*tmp_tokens)-> type == SPACER)
		(*tmp_tokens) = (*tmp_tokens)-> next;
	if ((*tmp_tokens)-> type == DOLLAR || (*tmp_tokens)-> type == WORD)
		expand = true;
	else
		expand = false;
	*limiter = ft_strdup((*tmp_tokens)-> content);
	free((*tmp_tokens)-> content);
	(*tmp_tokens)-> content = ft_strdup(tmp_file);
	(*tmp_tokens)-> type = WORD;
	(*tmp_tokens) = tmp;
	return (expand);
}

char	*tmp_file_name(void)
{
	char	*tmp_file;
	char	*fixed_file;
	int		i;

	i = 1;
	fixed_file = ft_strdup("/tmp/tmp_file");
	tmp_file = ft_strdup(fixed_file);
	while (access(tmp_file, F_OK) == 0)
	{
		free(tmp_file);
		tmp_file = ft_strjoin(fixed_file, ft_itoa(i), 2);
		i++;
	}
	free(fixed_file);
	return (tmp_file);
}

int	heredoc_handler(t_token **tmp_tokens, int input,
			int output, t_env *env)
{
	bool	expand;
	char	*limiter;
	char	*tmp_file;

	herdoc_signal();
	expand = false;
	limiter = NULL;
	tmp_file = tmp_file_name();
	expand = heredoc_expand_checker(tmp_tokens, expand, &limiter, tmp_file);
	output = fd_opener(tmp_file, 0);
	heredoc_readline(output, limiter, env, expand);
	input = fd_opener(tmp_file, 2);
	free(tmp_file);
	free(limiter);
	return (input);
}
