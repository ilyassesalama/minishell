/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_creator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:04:24 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/13 01:34:37 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
			ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_strdup(" "), SPACER));
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
			if (input[i] && input[i] == '?')
			{
				i++;
				ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_substr(input, start, i - start), DOLLAR));
			}
			else if (input[i] && ft_strchr("$+-./:;<=>@[\\]^`{|}~%#&()*,;=[]", input[i]))
			{
				i++;
				while (input[i] && !ft_strchr(" $\"'+-./:;<=>?@[\\]^`{|}~%#&()*,;=[]", input[i]))
					i++;
				ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_substr(input, start, i - start), WORD));
			}
			else
			{
				while (input[i] && !ft_strchr(" $\"'+-./:;<=>?@[\\]^`{|}~%#&()*,;=[]", input[i]))
					i++;
				ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_substr(input, start, i - start), DOLLAR));
			}
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
	tokens = ft_t_SPACERs_deleter(tokens);
	if (!syntax_error(tokens))
		return (NULL);
	tokens = tokens_expander(tokens, data);
	return (tokens);
}
