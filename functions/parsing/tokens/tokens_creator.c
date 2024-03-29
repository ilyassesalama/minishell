/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_creator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:04:24 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/25 21:09:42 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_token	*handle_dollar(char *input, int *i, t_token *tokens)
{
	int		start;
	char	*check;

	check = ft_strdup(" $\"'+-./:;<=>?@[\\]^`{|}~%#&()*,;=[]");
	start = *i;
	(*i)++;
	if (input[*i] && (input[*i] == '?'
			|| (input[*i] >= '0' && input[*i] <= '9')))
		(*i)++;
	else if (input[*i]
		&& ft_strchr("$+-./:;<=>@[\\]^`{|}~%#&()*,;=[]", input[*i]))
	{
		(*i)++;
		while (input[*i] && !ft_strchr(check, input[*i]))
			(*i)++;
		ft_t_lstadd_back(&tokens,
			ft_t_lstnew(ft_substr(input, start, *i - start), WORD));
		return (free (check), tokens);
	}
	else
		while (input[*i] && !ft_strchr(check, input[*i]))
			(*i)++;
	ft_t_lstadd_back(&tokens,
		ft_t_lstnew(ft_substr(input, start, *i - start), DOLLAR));
	return (free (check), tokens);
}

t_token	*tokens_checker(char *input, t_env *data)
{
	int		i;
	t_token	*tokens;

	(void)data;
	tokens = NULL;
	i = 0;
	while (input[i])
	{
		if (input[i] && (input[i] == ' ' || input[i] == '\t' || input[i] == '\n'
				|| input[i] == '\v' || input[i] == '\f' || input[i] == '\r'))
			tokens = handle_space(input, &i, tokens);
		else if (input[i] && input[i] == '\'')
			tokens = handle_singlequote(input, &i, tokens);
		else if (input[i] && input[i] == '\"')
			tokens = handle_doublequote(input, &i, tokens);
		else if (input[i] && (input[i] == '>' || input[i] == '<'))
			tokens = handle_special(input, &i, tokens);
		else if (input[i] && input[i] == '$')
			tokens = handle_dollar(input, &i, tokens);
		else
			tokens = handle_word(input, &i, tokens);
	}
	return (tokens);
}

void	tokens_empty_remover(t_token **tokens)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		if ((!tmp -> content || tmp -> content[0] == '\0')
			&& (tmp -> type == DOLLAR || tmp -> type == WORD))
			tmp -> type = NONUSABLE;
		tmp = tmp -> next;
	}
}

t_token	*tokens_creation(char *input, t_env *data)
{
	t_token	*tokens;

	tokens = tokens_checker(input, data);
	tokens = ft_t_spaces_deleter(tokens);
	if (!syntax_error(tokens))
		return (ft_t_lstclear(&tokens), NULL);
	tokens = tokens_expander(tokens, data);
	tokens_empty_remover(&tokens);
	return (tokens);
}
