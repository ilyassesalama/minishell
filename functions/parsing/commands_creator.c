/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_creator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 04:43:28 by tajjid            #+#    #+#             */
/*   Updated: 2023/05/21 00:14:05 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


t_command	*command_creator(t_token *tokens)
{
	t_command	*commands;
	t_command	*tmp;
	t_token		*tmp_tokens;
	int			input;
	int			output;
	
	tmp_tokens = tokens;
	commands = NULL;
	tmp = NULL;
	input = 0;
	output = 1;
	
	while (tmp_tokens)
	{
		if (tmp_tokens -> type == PIPE)
		{
			ft_c_lstadd_back(&commands, ft_c_lstnew("taha" , input, output));
			tmp = NULL;
			input = 0;
			output = 1;
		}
		else if (tmp_tokens -> type == HEREDOC)
		{
			input = fd_opener(tmp_tokens -> next->content, 0);
			output = 1;
		}
		else if (tmp_tokens -> type == APPEND)
		{
			if (tmp_tokens -> next -> type == WORD || tmp_tokens -> next -> type == SINGLE_QUOTE || tmp_tokens -> next -> type == DOUBLE_QUOTE)
			{
				output = fd_opener(tmp_tokens -> next->content, 1);
				tmp_tokens = tmp_tokens -> next;
			}
			else if ((tmp_tokens -> next -> type == SPACE && tmp_tokens -> next -> next -> type == WORD)
				|| (tmp_tokens -> next -> type == SPACE && tmp_tokens -> next -> next -> type == SINGLE_QUOTE)
				|| (tmp_tokens -> next -> type == SPACE && tmp_tokens -> next -> next -> type == DOUBLE_QUOTE))
			{
				output = fd_opener(tmp_tokens -> next -> next->content, 1);
				tmp_tokens = tmp_tokens -> next -> next;
			}
		}
		else if (tmp_tokens -> type == REDIR)
		{
			if (tmp_tokens -> next -> type == WORD || tmp_tokens -> next -> type == SINGLE_QUOTE || tmp_tokens -> next -> type == DOUBLE_QUOTE)
			{
				output = fd_opener(tmp_tokens -> next->content, 2);
				tmp_tokens = tmp_tokens -> next;
			}
			else if ((tmp_tokens -> next -> type == SPACE && tmp_tokens -> next -> next -> type == WORD)
				|| (tmp_tokens -> next -> type == SPACE && tmp_tokens -> next -> next -> type == SINGLE_QUOTE)
				|| (tmp_tokens -> next -> type == SPACE && tmp_tokens -> next -> next -> type == DOUBLE_QUOTE))
			{
				output = fd_opener(tmp_tokens -> next -> next->content, 2);
				tmp_tokens = tmp_tokens -> next -> next;
			}
		}
		else if (tmp_tokens -> type == DREDIR)
		{
			if (tmp_tokens -> next -> type == WORD || tmp_tokens -> next -> type == SINGLE_QUOTE || tmp_tokens -> next -> type == DOUBLE_QUOTE)
			{
				output = fd_opener(tmp_tokens -> next->content, 3);
				tmp_tokens = tmp_tokens -> next;
			}
			else if ((tmp_tokens -> next -> type == SPACE && tmp_tokens -> next -> next -> type == WORD)
				|| (tmp_tokens -> next -> type == SPACE && tmp_tokens -> next -> next -> type == SINGLE_QUOTE)
				|| (tmp_tokens -> next -> type == SPACE && tmp_tokens -> next -> next -> type == DOUBLE_QUOTE))
			{
				output = fd_opener(tmp_tokens -> next -> next->content, 3);
				tmp_tokens = tmp_tokens -> next -> next;
			}
		}
		tmp_tokens = tmp_tokens -> next;
	}
	ft_c_lstadd_back(&commands, ft_c_lstnew("taha", input, output));
	return (commands);
}