/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_creator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:54:19 by tajjid            #+#    #+#             */
/*   Updated: 2023/05/19 21:38:47 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token		*tokens_creation(char *input, t_env *data)
{
	int 	i;
	int 	start;
	
	t_token *tokens = NULL;
	
	i = 0;
	while(input[i])
	{
		if (input[i] && input[i] == ' ')
		{
			ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_strdup(" "), SPACE));
			while (input[i] == ' ')
				i++;
		}
		else if (input[i] && input[i] == '\'')
		{
			i++;
			start = i;
			while (input[i] && input[i] != '\'')
				i++;
			ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_substr(input, start, i - start), SINGLE_QUOTE));
			i++;
		}
		else if (input[i] && input[i] == '\"')
		{
			i++;
			start = i;
			while (input[i] && input[i] != '\"')
				i++;
			ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_substr(input, start, i - start), DOUBLE_QUOTE));
			i++;
		}
		else if (input[i] && input[i] == '|')
		{
			ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_strdup("|"), PIPE));
			i++;
		}
		else if ((input[i] && input[i + 1]) && input[i] == '>' && input[i + 1] == '>')
		{
			ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_strdup(">>"), APPEND));
			i += 2;
		}
		else if ((input[i] && input[i + 1]) && input[i] == '<' && input[i + 1] == '<')
		{
			ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_strdup("<<"), HEREDOC));
			i += 2;
		}
		else if (input[i] && input[i] == '>')
		{
			ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_strdup(">"), REDIR));
			i++;
		}
		else if (input[i] && input[i] == '<')
		{
			ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_strdup("<"), DREDIR));
			i++;
		}
		else if (input[i] && input[i] == '$')
		{
			start = i;
			i++;
			while (input[i] && input[i] != ' ' && input[i] != '|' 
				&& input[i] != '>' && input[i] != '<' && input[i] != '$'
				&& input[i] != '\'' && input[i] != '\"')
				i++;
			ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_substr(input, start, i - start), DOLLAR));
		}
		else 
		{
			start = i;
			while(input[i] && input[i] != ' ' && input[i] != '|' 
				&& input[i] != '>' && input[i] != '<' && input[i] != '$'
				&& input[i] != '\'' && input[i] != '\"')
				i++;
			ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_substr(input, start, i - start), WORD));
		}
	}
	if (tokens && tokens -> type == SPACE)
	{
		t_token *tmp = tokens->next;
		free(tokens);
		tokens = tmp;
	}
	if (tokens && ft_t_lstlast(tokens) -> type == SPACE)
	{
		t_token *tmp = ft_t_lstlast(tokens);
		free(tmp);
		tmp = NULL;
		tmp = ft_t_blstlast(tokens);
		tmp -> next = NULL;
	}
	tokens = tokens_expander(tokens, data);
	syntax_error(tokens);
	return (tokens);
}
