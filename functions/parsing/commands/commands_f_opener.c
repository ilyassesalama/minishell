/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_f_opener.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 06:31:06 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/17 00:32:05 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	fd_opener(char *file, int mode)
{
	int	fd;

	fd = 0;
	if (mode == OUT_REDIR || mode == 0)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (mode == APPEND || mode == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (mode == IN_REDIR || mode == 2)
		fd = open(file, O_RDONLY, 0777);
	return (fd);
}

bool	files_if_checker(t_token *tmp_tokens)
{
	if ((tmp_tokens -> next -> type == SPACER
			&& tmp_tokens -> next -> next -> type == WORD)
		|| (tmp_tokens -> next -> type == SPACER
			&& tmp_tokens -> next -> next -> type == SINGLE_QUOTE)
		|| (tmp_tokens -> next -> type == SPACER
			&& tmp_tokens -> next -> next -> type == DOUBLE_QUOTE))
		return (true);
	return (false);
}

void	dredir_opener(t_token **tmp_tokens, int type, int *input)
{
	if ((*tmp_tokens)-> next -> type == WORD
		|| (*tmp_tokens)-> next -> type == SINGLE_QUOTE
		|| (*tmp_tokens)-> next -> type == DOUBLE_QUOTE)
	{
		if (*input != 0)
			close(*input);
		*input = fd_opener((*tmp_tokens)-> next -> content, type);
		(*tmp_tokens)-> type = NONUSABLE;
		(*tmp_tokens)-> next -> type = NONUSABLE;
		(*tmp_tokens) = (*tmp_tokens)-> next;
	}
	else if (files_if_checker((*tmp_tokens)))
	{
		if (*input != 0)
			close(*input);
		*input = fd_opener((*tmp_tokens)-> next -> next -> content, type);
		(*tmp_tokens)-> type = NONUSABLE;
		(*tmp_tokens)-> next -> type = NONUSABLE;
		(*tmp_tokens)-> next -> next -> type = NONUSABLE;
		(*tmp_tokens) = (*tmp_tokens)-> next -> next;
	}
}

void	files_opener(t_token **tmp_tokens, int type, int *output)
{
	if ((*tmp_tokens)-> next -> type == WORD
		|| (*tmp_tokens)-> next -> type == SINGLE_QUOTE
		|| (*tmp_tokens)-> next -> type == DOUBLE_QUOTE)
	{
		if (*output != 1)
			close(*output);
		*output = fd_opener((*tmp_tokens)-> next -> content, type);
		(*tmp_tokens)-> type = NONUSABLE;
		(*tmp_tokens)-> next -> type = NONUSABLE;
		(*tmp_tokens) = (*tmp_tokens)-> next;
	}
	else if (files_if_checker((*tmp_tokens)))
	{
		if (*output != 1)
			close(*output);
		*output = fd_opener((*tmp_tokens)-> next -> next -> content, type);
		(*tmp_tokens)-> type = NONUSABLE;
		(*tmp_tokens)-> next -> type = NONUSABLE;
		(*tmp_tokens)-> next -> next -> type = NONUSABLE;
		(*tmp_tokens) = (*tmp_tokens)-> next -> next;
	}
}
