/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_creator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 04:43:28 by tajjid            #+#    #+#             */
/*   Updated: 2023/06/15 02:20:13 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


/*
TODO: whenever you find a word split with space
TODO: fill the command list with the commands
*/

// t_command	*command_filler(t_token *tokens, t_command *commands, int input, int output)
// {
// 	char		*command;
// 	char		**tmp2d;
// 	char		**args;
	
// 	while(tokens -> type != PIPE)
// 	{
// 		tokens = tokens -> next;
// 	}
// 	return (commands);
// }

t_command	*command_creator(t_token *tokens)
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
	
	tmp_tokens = tokens;
	tmp_tokens2 = tokens;
	commands = NULL;
	tmp = NULL;
	input = 0;
	output = 1;
	flag = 0;

	while (tmp_tokens)
	{
		non_use_remover(tokens);
		// if (flag == 1)
		// {
		// 	tmp_tokens2 = tmp_tokens;
		// 	flag = 0;
		// }
		// if (tmp_tokens -> type == PIPE)
		// {
		// 	commands = command_filler(tmp_tokens2, commands, input, output);
		// 	input = 0;
		// 	output = 1;
		// 	flag = 1;
		// 	tmp_tokens = tmp_tokens -> next;
		// }
		if (tmp_tokens -> type == HEREDOC)
		{
			output = fd_opener("tmp.txt", 2);
			line = readline("> ");
			if (tmp_tokens -> next -> type != SPACE)
			{
				limiter = ft_strdup(tmp_tokens -> next -> content);
				tmp_tokens -> type = NONUSABLE;
				tmp_tokens -> next -> type = NONUSABLE;
			}
			else
			{
				limiter = ft_strdup(tmp_tokens -> next -> next -> content);
				tmp_tokens -> type = NONUSABLE;
				tmp_tokens -> next -> type = NONUSABLE;
				tmp_tokens -> next -> next -> type = NONUSABLE;
			}
			while(line && ft_strcmp(line, limiter))
			{
				if (line)
					free(line);
				line = readline("> ");
				write(output, line, ft_strlen(line));
				write(output, "\n", 1);
			}	
			input = fd_opener("tmp.txt", 3);
			output = 1;
		}
		else if (tmp_tokens -> type == APPEND)
		{
			if (tmp_tokens -> next -> type == WORD || tmp_tokens -> next -> type == SINGLE_QUOTE || tmp_tokens -> next -> type == DOUBLE_QUOTE)
			{
				output = fd_opener(tmp_tokens -> next->content, 2);
				tmp_tokens -> type = NONUSABLE;
				tmp_tokens -> next -> type = NONUSABLE;
				tmp_tokens = tmp_tokens -> next;
			}
			else if ((tmp_tokens -> next -> type == SPACE && tmp_tokens -> next -> next -> type == WORD)
				|| (tmp_tokens -> next -> type == SPACE && tmp_tokens -> next -> next -> type == SINGLE_QUOTE)
				|| (tmp_tokens -> next -> type == SPACE && tmp_tokens -> next -> next -> type == DOUBLE_QUOTE))
			{
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
			else if ((tmp_tokens -> next -> type == SPACE && tmp_tokens -> next -> next -> type == WORD)
				|| (tmp_tokens -> next -> type == SPACE && tmp_tokens -> next -> next -> type == SINGLE_QUOTE)
				|| (tmp_tokens -> next -> type == SPACE && tmp_tokens -> next -> next -> type == DOUBLE_QUOTE))
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
			else if ((tmp_tokens -> next -> type == SPACE && tmp_tokens -> next -> next -> type == WORD)
				|| (tmp_tokens -> next -> type == SPACE && tmp_tokens -> next -> next -> type == SINGLE_QUOTE)
				|| (tmp_tokens -> next -> type == SPACE && tmp_tokens -> next -> next -> type == DOUBLE_QUOTE))
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
	// commands = command_filler(tmp_tokens2, commands, input, output);
	return (commands);
}
