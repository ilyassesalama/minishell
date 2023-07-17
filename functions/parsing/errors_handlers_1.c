/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handlers_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 23:11:35 by isalama           #+#    #+#             */
/*   Updated: 2023/07/17 01:09:24 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	handle_quotes(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote = input[i];
			i++;
			while (input[i] && input[i] != quote)
				i++;
			if (input[i] != quote)
				return (out_error(ERROR_MSG_QUOTE), false);
			else
				i++;
		}
		else
			i++;
	}
	return (true);
}

bool	syntax_error_1(t_token *tokens)
{
	if (tokens -> type == PIPE)
	{
		if (tokens -> next == NULL || tokens -> next -> type == PIPE)
			return (out_error(ERROR_MSG_SYNTAX), true);
		if (tokens -> next -> next && tokens -> next -> type == SPACER
			&& tokens -> next -> next -> type == PIPE)
			return (out_error(ERROR_MSG_SYNTAX), true);
	}
	else if ((tokens -> type == OUT_REDIR || tokens -> type == IN_REDIR)
		&& tokens -> next == NULL)
		return (out_error(ERROR_MSG_SYNTAX), true);
	else if ((tokens -> type == APPEND || tokens -> type == HEREDOC)
		&& tokens -> next == NULL)
		return (out_error(ERROR_MSG_SYNTAX), true);
	return (false);
}

bool	syntax_error_2(t_token *tokens)
{
	if (tokens -> next && tokens -> type == APPEND)
	{
		if (tokens -> next -> type == APPEND
			|| tokens -> next -> type == PIPE)
			return (out_error(ERROR_MSG_SYNTAX), true);
		else if (tokens -> next -> type == SPACER
			&& (tokens -> next -> next -> type == HEREDOC
				|| tokens -> next -> next -> type == APPEND))
			return (out_error(ERROR_MSG_SYNTAX), true);
	}
	else if (tokens -> next && tokens -> type == HEREDOC)
	{
		if (tokens -> next -> type == HEREDOC
			|| tokens -> next -> type == PIPE)
			return (out_error(ERROR_MSG_SYNTAX), true);
		else if (tokens -> next -> type == SPACER
			&& (tokens -> next -> next -> type == HEREDOC
				|| tokens -> next -> next -> type == APPEND))
			return (out_error(ERROR_MSG_SYNTAX), true);
	}
	return (false);
}

bool	syntax_error_3(t_token *tokens)
{
	if (tokens -> next && tokens -> type == OUT_REDIR)
	{
		if (tokens -> next -> type == IN_REDIR
			|| tokens -> next -> type == PIPE)
			return (out_error(ERROR_MSG_SYNTAX), true);
		else if (tokens -> next -> type == SPACER
			&& (tokens -> next -> next -> type == OUT_REDIR
				|| tokens -> next -> next -> type == IN_REDIR))
			return (out_error(ERROR_MSG_SYNTAX), true);
	}
	else if (tokens -> next && tokens -> type == IN_REDIR)
	{
		if (tokens -> next -> type == OUT_REDIR
			|| tokens -> next -> type == PIPE
			|| tokens -> next -> type == IN_REDIR)
			return (out_error(ERROR_MSG_SYNTAX), true);
		else if (tokens -> next -> type == SPACER
			&& (tokens -> next -> next -> type == OUT_REDIR
				|| tokens -> next -> next -> type == IN_REDIR
				|| tokens -> next -> next -> type == PIPE))
			return (out_error(ERROR_MSG_SYNTAX), true);
	}
	return (false);
}

bool	syntax_error(t_token *tokens)
{
	if (tokens && tokens -> type == PIPE)
		return (out_error(ERROR_MSG_SYNTAX), false);
	while (tokens)
	{
		if (syntax_error_1(tokens) || syntax_error_2(tokens)
			|| syntax_error_3(tokens))
			return (false);
		tokens = tokens -> next;
	}
	return (true);
}
