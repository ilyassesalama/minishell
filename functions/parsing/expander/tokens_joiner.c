/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_joiner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 05:05:03 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/25 10:44:44 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	content_joiner(t_token **tmp, t_token *tokens, int type)
{
	char	*tmp_content;
	char	*tmp_content2;
	t_token	*tmp2;

	tmp_content = NULL;
	tmp_content2 = NULL;
	tmp2 = NULL;
	tmp_content = (*tmp)-> content;
	tmp_content2 = (*tmp)-> next -> content;
	tmp2 = (*tmp)-> next -> next;
	free((*tmp)-> next);
	(*tmp)-> content = ft_strjoin(tmp_content, tmp_content2, 1);
	free(tmp_content2);
	(*tmp)-> type = type;
	(*tmp)-> next = tmp2;
	(*tmp) = tokens;
}

void	dollar_joiner(t_token **tmp, t_token *tokens)
{
	if (ft_strlen((*tmp)-> content) == 1)
	{
		if ((*tmp)-> content[0] != '$')
			(*tmp)-> type = WORD;
		else
		{
			free((*tmp)-> content);
			(*tmp)-> content = ft_strdup("");
			(*tmp)-> type = NONUSABLE;
		}
	}
	else
		content_joiner(tmp, tokens, DOLLAR);
}

void	token_join_checker(t_token **tmp, t_token *tokens)
{
	if (((*tmp) && (*tmp)-> next) && ((*tmp)-> type == WORD
			&& (*tmp)-> next -> type == SINGLE_QUOTE))
		content_joiner(tmp, tokens, SINGLE_QUOTE);
	else if (((*tmp) && (*tmp)-> next) && ((*tmp)-> type == WORD
			&& (*tmp)-> next -> type == DOUBLE_QUOTE))
		content_joiner(tmp, tokens, DOUBLE_QUOTE);
	else if (((*tmp) && (*tmp)-> next) && ((*tmp)-> type == WORD
			&& join_checker((*tmp)-> next -> type)))
		content_joiner(tmp, tokens, WORD);
	else if (((*tmp) && (*tmp)-> next) && ((*tmp)-> type == DOUBLE_QUOTE
			&& join_checker((*tmp)-> next -> type)))
		content_joiner(tmp, tokens, DOUBLE_QUOTE);
	else if (((*tmp) && (*tmp)-> next) && ((*tmp)-> type == SINGLE_QUOTE
			&& join_checker((*tmp)-> next -> type)))
		content_joiner(tmp, tokens, SINGLE_QUOTE);
	else if (((*tmp) && (*tmp)-> next) && ((*tmp)-> type == DOLLAR
			&& join_checker((*tmp)-> next -> type)))
		dollar_joiner(tmp, tokens);
	else
		(*tmp) = (*tmp)-> next;
}

t_token	*tokens_joiner(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
		token_join_checker(&tmp, tokens);
	return (tokens);
}
