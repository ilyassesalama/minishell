/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanders_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 05:05:14 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/16 02:18:49 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

bool	join_checker(int type)
{
	int	i;
	int	types[6];

	i = 0;
	types[0] = HEREDOC;
	types[1] = REDIR;
	types[2] = APPEND;
	types[3] = DREDIR;
	types[4] = PIPE;
	types[5] = SPACER;
	while (i < 6)
	{
		if (type == types[i])
			return (false);
		i++;
	}
	return (true);
}

char	*d_expander(char *str, t_env *data)
{
	int		i;
	char	*tmp;

	i = 0;
	if (str[i] && str[i] == '?')
	{
		tmp = ft_itoa(g_global.exit_status);
		str = ft_strjoin(tmp, str + 1, 0);
		return (str);
	}
	while (str[i] && !ft_strchr(" $\"'+-./:;<=>@[\\]^`{|}~%#&()*,;=[]", str[i]))
		i++;
	if (i == 0)
		return (ft_strjoin("$", str, 0));
	tmp = ft_substr(str, 0, i);
	while (data && ft_strcmp(data -> key, tmp) != 0)
		data = data -> next;
	if (data)
		tmp = ft_strdup(data -> value);
	else
		tmp = ft_strdup("");
	return (tmp);
}

char	*chack_expand1(int *i, char *str, char *tmp, t_env *data)
{
	char	*tmp2;

	tmp2 = NULL;
	(*i)++;
	tmp2 = d_expander(str + (*i), data);
	tmp = ft_strjoin(tmp, tmp2, 2);
	while (str[(*i)]
		&& !ft_strchr(" $\"'+-./:;<=>@[\\]^`{|}~%#&()*,;=[]", str[(*i)]))
		(*i)++;
	return (tmp);
}

char	*chack_expand2(int *i, char *str, char *tmp)
{
	int		j;
	char	*tmp2;

	tmp2 = NULL;
	j = (*i);
	if (str[j] && str[j] == '$')
		j++;
	while (str[j] && str[j] != '$')
		j++;
	j = j - (*i);
	tmp2 = ft_substr(str, (*i), j);
	tmp = ft_strjoin(tmp, tmp2, 2);
	(*i) += j;
	return (tmp);
}

char	*d_quote_expander(char *str, t_env *data)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = ft_strdup("");
	tmp2 = NULL;
	while (str[i])
	{
		if (str[i] && str[i + 1] && str[i] == '$' && str[i + 1] == '$')
		{
			tmp = ft_strjoin(tmp, "$$", 0);
			i += 2;
		}
		else if (str[i] && str[i + 1] && str[i] == '$'
			&& !ft_strchr(" $\"'+-./:;<=>@[\\]^`{|}~%#&()*,;=[]", str[i + 1]))
			tmp = chack_expand1(&i, str, tmp, data);
		else
			tmp = chack_expand2(&i, str, tmp);
	}
	return (tmp);
}
