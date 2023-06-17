/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 02:10:00 by tajjid            #+#    #+#             */
/*   Updated: 2023/06/17 23:58:28 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*

*/
char *check_expand(char *str, t_env *data)
{
	int i = 0;
	char *tmp;
	
	while (str[i] && !ft_strchr(" $\"'+-./:;<=>?@[\\]^`{|}~%#&()*,;=[]", str[i]))
		i++;
	tmp = ft_substr(str, 0, i);
	while (data && ft_strcmp(data -> key, tmp) != 0)
		data = data -> next;
	if (data)
		tmp = ft_strdup(data -> value);
	else
		tmp = ft_strdup("");
	str = ft_strjoin(tmp, str + i, 1);
	return (str);
}

char *d_quote_expander(char *str, t_env *data)
{
	int boo = 0;
	int boo2 = 0;
	int i = 0;
	char **splitted;
	char *tmp = ft_strdup("") ;
	
	if (str[0] == '$')
		boo = 1;
	if (str[1] && ft_strchr("$\"'+-./:;<=>?@[\\]^`{|}~%#&()*,;=[]", str[1]))
		boo2 = 1;
	splitted  = ft_split(str, '$');
	while (splitted[i])
	{
		if (boo == 1 && i == 0)
			splitted[i] = check_expand(splitted[i], data);
		else if (i != 0)
			splitted[i] = check_expand(splitted[i], data);
		i++;
	}
	splitted[i] = NULL;
	i = 0;
	if (boo2 == 1)
		tmp = ft_strjoin(tmp, "$", 0);
	while(splitted[i])
		tmp = ft_strjoin(tmp, splitted[i++], 2);
	return (tmp);
}

char *word_expander(char *str, t_env *data)
{
	char *tmp;
	
	while (data && ft_strcmp(data -> key, str + 1) != 0)
		data = data -> next;
	if (data)
		tmp = ft_strdup(data -> value);
	else
		tmp = ft_strdup("");
	return (tmp);
}

bool	join_checker(int type)
{

	int i = 0;
	int types[6] = {HEREDOC, REDIR, APPEND, DREDIR, PIPE, SPACE};
	
	while(i < 5){
		if (type == types[i])
			return (false);
		i++;
	}
	return (true);
}

t_token		*tokens_joiner(t_token *tokens)
{
	t_token *tmp;
	char *tmp_content = NULL;
	char *tmp_content2 = NULL;
	
	tmp = tokens;
	while (tmp)
	{
		if ((tmp && tmp -> next) && (tmp -> type == WORD && join_checker(tmp -> next -> type)))
		{
			tmp_content = tmp -> content;
			tmp_content2 = tmp -> next -> content;
			tmp -> content = ft_strjoin(tmp_content, tmp_content2, 1);
			free(tmp_content2);
			tmp -> type = WORD;
			tmp -> next = tmp -> next -> next;
			tmp = tokens;
		}
		else if ((tmp && tmp -> next) && (tmp -> type == DOUBLE_QUOTE && join_checker(tmp -> next -> type)))
		{
			tmp_content = tmp -> content;
			tmp_content2 = tmp -> next -> content;
			tmp -> content = ft_strjoin(tmp_content, tmp_content2, 1);
			free(tmp_content2);
			tmp -> type = DOUBLE_QUOTE;
			tmp -> next = tmp -> next -> next;
			tmp = tokens;
		}
		else if ((tmp && tmp -> next) && (tmp -> type == SINGLE_QUOTE && join_checker(tmp -> next -> type)))
		{
			tmp_content = tmp -> content;
			tmp_content2 = tmp -> next -> content;
			tmp -> content = ft_strjoin(tmp_content, tmp_content2, 1);
			free(tmp_content2);
			tmp -> type = SINGLE_QUOTE;
			tmp -> next = tmp -> next -> next;
			tmp = tokens;
		}
		else if ((tmp && tmp -> next) && (tmp -> type == DOLLAR && join_checker(tmp -> next -> type)))
		{
			tmp_content = tmp -> content;
			tmp_content2 = tmp -> next -> content;
			tmp -> content = ft_strjoin(tmp_content, tmp_content2, 1);
			free(tmp_content2);
			tmp -> type = DOLLAR;
			tmp -> next = tmp -> next -> next;
			tmp = tokens;
		}
		else
			tmp = tmp -> next;
	}
	return (tokens);
}

t_token		*tokens_expander(t_token *tokens, t_env *data)
{
	t_token *tmp;
	t_token *tmp2;
	t_env	*tmp_env;
	int		i;
	int		j;
	char	*tmp_content;

	i = 0;
	j = 0;
	tmp = tokens;
	tmp2 = tokens;
	tmp_env = data;
	
	while (tmp)
	{
		data = tmp_env;
		if (tmp -> type == HEREDOC)
		{
			tmp = tmp -> next;
			if (tmp -> type == SPACE)
				tmp = tmp -> next;
			while (tmp && (tmp -> type == WORD 
					|| tmp -> type == SINGLE_QUOTE 
					|| tmp -> type == DOUBLE_QUOTE))
				tmp = tmp -> next;
		}
		if (tmp && (tmp -> type == DOLLAR))
		{
			tmp_content = tmp -> content;
			tmp -> content = word_expander(tmp_content, data);
			tmp -> type = WORD;
		}
		else if (tmp && (tmp -> type == DOUBLE_QUOTE))
		{
			tmp_content = tmp -> content;
			tmp -> content = d_quote_expander(tmp_content, data);
			tmp -> type = DOUBLE_QUOTE;
		}
		tmp = tmp -> next;
	}
	tmp = tokens;
	tmp = tokens_joiner(tmp);
	return (tokens);
}
