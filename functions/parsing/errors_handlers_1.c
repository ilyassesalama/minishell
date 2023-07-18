/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handlers_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 23:11:35 by isalama           #+#    #+#             */
/*   Updated: 2023/07/18 06:30:01 by isalama          ###   ########.fr       */
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

bool	syntax_error_checker(t_token *tokens)
{
	if (tokens -> type == PIPE || tokens -> type == IN_REDIR
		|| tokens -> type == OUT_REDIR || tokens -> type == APPEND
		|| tokens -> type == HEREDOC)
	{
		if (tokens -> next && tokens -> next -> type == SPACER)
			tokens = tokens -> next;
		if (tokens -> next == NULL || tokens -> next -> type == PIPE
			|| tokens -> next -> type == IN_REDIR
			|| tokens -> next -> type == OUT_REDIR
			|| tokens -> next -> type == APPEND
			|| tokens -> next -> type == HEREDOC)
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
		if (syntax_error_checker(tokens))
			return (false);
		tokens = tokens -> next;
	}
	return (true);
}
