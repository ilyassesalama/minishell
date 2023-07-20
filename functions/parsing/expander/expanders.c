/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 02:10:00 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/20 01:24:38 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*word_expander(char *str, t_env *data)
{
	char	*tmp;

	if (str[0] == '$' && str[1] == '?')
		return (ft_itoa(g_global.exit_status));
	else if (str[0] == '$' && str[1] == '$')
		return (ft_strdup("$$"));
	else if (str[0] == '$' && str[1] == '\0')
		return (ft_strdup("$"));
	while (data)
	{
		if (ft_strcmp(data -> key, str + 1) == 0 && !data->is_hidden)
			break ;
		data = data -> next;
	}
	if (data)
		tmp = ft_strdup(data -> value);
	else
		tmp = ft_strdup("");
	return (tmp);
}

void	expand_token_checker(t_env *data, t_token **tmp)
{
	char	*tmp_content;

	if ((*tmp) && ((*tmp)-> type == DOLLAR))
	{
		tmp_content = (*tmp)-> content;
		(*tmp)-> content = word_expander(tmp_content, data);
		free(tmp_content);
		if (ft_strlen((*tmp)-> content) == 1
			&& (*tmp)-> next && (*tmp)-> next -> type != SPACER)
			(*tmp)-> type = DOLLAR;
		else
			(*tmp)-> type = WORD;
		(*tmp) = (*tmp)-> next;
	}
	else if ((*tmp) && ((*tmp)-> type == DOUBLE_QUOTE))
	{
		tmp_content = (*tmp)-> content;
		(*tmp)-> content = d_quote_expander(tmp_content, data);
		free(tmp_content);
		(*tmp)-> type = DOUBLE_QUOTE;
		(*tmp) = (*tmp)-> next;
	}
	else
		(*tmp) = (*tmp)-> next;
}

t_token	*tokens_expander(t_token *tokens, t_env *data)
{
	t_token	*tmp;
	t_env	*tmp_env;

	tmp = tokens;
	tmp_env = data;
	while (tmp)
	{
		data = tmp_env;
		if (tmp -> type == HEREDOC)
		{
			tmp = tmp -> next;
			if (tmp -> type == SPACER)
				tmp = tmp -> next;
			while (tmp && (tmp -> type == DOLLAR || tmp -> type == SINGLE_QUOTE
					|| tmp -> type == DOUBLE_QUOTE))
				tmp = tmp -> next;
		}
		else
			expand_token_checker(data, &tmp);
	}
	tmp = tokens;
	tmp = tokens_joiner(tmp);
	return (tokens);
}
