/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handlers_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 23:11:35 by isalama           #+#    #+#             */
/*   Updated: 2023/05/20 02:01:09 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*

*/

void	out_error(char *error_message)
{
	ft_putstr_fd(error_message, 2);
}

bool	handle_quotes(char *input)
{
	int i;
	
	i = 0;
	while(input[i])
	{
		if (input[i] == '\'')
		{
			i++;
			while (input[i] && input[i] != '\'')
				i++;
			if (input[i] == '\'')
				i++;
			else
				return(out_error(ERROR_MSG_QUOTE), false);
		}
		if (input[i] == '\"')
		{
			i++;
			while (input[i] && input[i] != '\"')
				i++;
			if (input[i] == '\"')
				i++;
			else 
				return(out_error(ERROR_MSG_QUOTE), false);
		}
		if (input[i] != '\'' && input[i] != '\"')
			i++;
	}
	return true;
}

bool	syntax_error(t_token *tokens)
{
	if (tokens && tokens -> type == PIPE)
		return (out_error(ERROR_MSG_SYNTAX), false);
	while (tokens)
	{
		if (tokens -> type == PIPE)
		{
			if (tokens -> next == NULL || tokens -> next -> type == PIPE)
				return (out_error(ERROR_MSG_SYNTAX), false);
			if (tokens -> next -> next && tokens -> next -> type == SPACE && tokens -> next -> next -> type == PIPE)
				return (out_error(ERROR_MSG_SYNTAX), false);
		}
		else if ((tokens -> type == REDIR || tokens -> type == DREDIR) && tokens -> next == NULL)
			return (out_error(ERROR_MSG_SYNTAX), false);
		else if ((tokens -> type == APPEND || tokens -> type == HEREDOC) && tokens -> next == NULL)
				return (out_error(ERROR_MSG_SYNTAX), false);
		else if (tokens -> next && tokens -> type == REDIR)
		{
			if (tokens -> next -> type == DREDIR || tokens -> next -> type == PIPE)
				return (out_error(ERROR_MSG_SYNTAX), false);
			else if (tokens -> next -> type == SPACE 
			&& (tokens -> next -> next -> type == REDIR || tokens -> next -> next -> type == DREDIR))
				return (out_error(ERROR_MSG_SYNTAX), false);
		}
		else if (tokens -> next && tokens -> type == DREDIR)
		{
			if (tokens -> next -> type == REDIR || tokens -> next -> type == PIPE)
				return (out_error(ERROR_MSG_SYNTAX), false);
			else if (tokens -> next -> type == SPACE 
			&& (tokens -> next -> next -> type == REDIR || tokens -> next -> next -> type == DREDIR))
				return (out_error(ERROR_MSG_SYNTAX), false);
		}
		tokens = tokens->next;
	}
	return true;
}
