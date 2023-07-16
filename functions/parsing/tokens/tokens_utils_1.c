/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 02:58:34 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/15 05:00:42 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_token	*handle_space(char *input, int *i, t_token *tokens)
{
	ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_strdup(" "), SPACER));
	while (input[*i] && input[*i] == ' ')
		(*i)++;
	return (tokens);
}

t_token	*handle_singlequote(char *input, int *i, t_token *tokens)
{
	int		j;
	char	*str;

	j = *i + 1;
	while (input[j] && input[j] != '\'')
		j++;
	str = ft_substr(input, *i + 1, j - *i - 1);
	ft_t_lstadd_back(&tokens, ft_t_lstnew(str, SINGLE_QUOTE));
	*i = j + 1;
	return (tokens);
}

t_token	*handle_doublequote(char *input, int *i, t_token *tokens)
{
	int		j;
	char	*str;

	j = *i + 1;
	while (input[j] && input[j] != '\"')
		j++;
	str = ft_substr(input, *i + 1, j - *i - 1);
	ft_t_lstadd_back(&tokens, ft_t_lstnew(str, DOUBLE_QUOTE));
	*i = j + 1;
	return (tokens);
}

t_token	*handle_special(char *input, int *i, t_token *tokens)
{
	if ((input[*i] && input[*i + 1])
		&& input[*i] == '>' && input[*i + 1] == '>')
	{
		ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_strdup(">>"), APPEND));
		(*i) += 2;
	}
	else if ((input[*i] && input[*i + 1])
		&& input[*i] == '<' && input[*i + 1] == '<')
	{
		ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_strdup("<<"), HEREDOC));
		(*i) += 2;
	}
	else if (input[*i] && input[*i] == '>')
	{
		ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_strdup(">"), REDIR));
		(*i)++;
	}
	else if (input[*i] && input[*i] == '<')
	{
		ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_strdup("<"), DREDIR));
		(*i)++;
	}
	return (tokens);
}

t_token	*handle_word(char *input, int *i, t_token *tokens)
{
	int		j;
	char	*str;

	j = *i;
	if (input[j] && input[j] == '|')
	{
		ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_strdup("|"), PIPE));
		j++;
	}
	else
	{
		while (input[j] && input[j] != ' ' && input[j] != '\"'
			&& input[j] != '\'' && input[j] != '$' && input[j] != '|'
			&& input[j] != '>' && input[j] != '<')
			j++;
		str = ft_substr(input, *i, j - *i);
		ft_t_lstadd_back(&tokens, ft_t_lstnew(str, WORD));
	}
	*i = j;
	return (tokens);
}