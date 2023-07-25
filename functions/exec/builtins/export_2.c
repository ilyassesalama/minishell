/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 00:37:19 by isalama           #+#    #+#             */
/*   Updated: 2023/07/25 17:36:20 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

bool	is_export_has_value(t_env *env, char *key)
{
	t_env	*tmp_env;

	tmp_env = env;
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->key, key) == 0 && !tmp_env->is_hidden)
		{
			if (tmp_env->value)
				return (true);
			else
				return (false);
		}
		tmp_env = tmp_env->next;
	}
	return (false);
}

void	export_append(t_env **env, int plus_pos, char *ident)
{
	char	*key;
	char	*value;
	t_env	*env_tmp;

	env_tmp = *env;
	key = ft_substr(ident, 0, plus_pos);
	while (env_tmp)
	{
		if (ft_strcmp(env_tmp->key, key) == 0 && !env_tmp->is_hidden)
		{
			if (ft_strlen(ident) > 3)
				value = ft_strjoin(env_tmp->value, ident + plus_pos
						+ 2, 0);
			else
				value = ft_strdup("");
			return (free(env_tmp->value), env_tmp->value = value, free(key));
		}
		env_tmp = env_tmp->next;
	}
	if (!ident[plus_pos] || (ident[plus_pos] && !ident[plus_pos + 1]))
		value = ft_strdup("");
	else
		value = ft_substr(ident, plus_pos + 2,
				ft_strlen(ident + plus_pos + 2));
	ft_lstadd_back(env, ft_envlstnew(key, value));
}

void	export_new_rest(char *identifier, int index,
			bool is_equal, char **value)
{
	if (!identifier[index] || !identifier[index + 1])
	{
		if (is_equal)
			(*value) = ft_strdup("");
		else
			(*value) = NULL;
	}
	else
		(*value) = ft_substr(identifier, index + 1,
				ft_strlen(identifier + index));
}

void	export_new(t_env **env, int index, char *identifier, bool is_equal)
{
	char	*key;
	char	*value;
	t_env	*tmp_env;

	tmp_env = *env;
	key = ft_substr(identifier, 0, index);
	if (is_export_has_value(*env, key) && !is_equal)
		return (free(key));
	while (tmp_env)
	{
		if (ft_strcmp(tmp_env->key, key) == 0 && !tmp_env->is_hidden)
			return (export_new_rest(identifier, index, is_equal, &value),
				free(tmp_env->value), tmp_env->value = value, free(key));
		tmp_env = tmp_env->next;
	}
	if (!identifier[index] || (identifier[index] && !identifier[index + 1]))
	{
		if (is_equal)
			value = ft_strdup("");
		else
			value = NULL;
	}
	else
		value = ft_substr(identifier, index + 1, ft_strlen(identifier + index));
	ft_lstadd_back(env, ft_envlstnew(key, value));
}
