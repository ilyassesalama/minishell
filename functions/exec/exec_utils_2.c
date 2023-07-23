/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:11:11 by isalama           #+#    #+#             */
/*   Updated: 2023/07/23 10:23:23 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_current_path(t_env *env)
{
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)) != NULL)
		return (ft_strdup(path));
	else
		ft_putstr_fd(ERROR_MSG_CD_ERR, 2);
	return (ft_strdup(get_env_value("PWD", env)));
}

void	update_env(char *key, char *value, t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			free(temp->value);
			temp->value = value;
			return ;
		}
		temp = temp->next;
	}
	free(value);
}

char	*get_env_value(char *key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	get_env_size(t_env *env)
{
	int		i;
	t_env	*temp;

	temp = env;
	i = 0;
	while (temp)
	{
		if (!temp->is_hidden)
			i++;
		temp = temp->next;
	}
	return (i);
}

char	**env_to_array(t_env *env)
{
	int		i;
	char	**env_variables;

	i = 0;
	env_variables = (char **)malloc(sizeof(char *) * (get_env_size(env) + 1));
	if (!env_variables)
		return (NULL);
	i = 0;
	while (env)
	{
		if (!env->is_hidden)
		{
			env_variables[i] = ft_strjoin(env->key, "=", 0);
			env_variables[i] = ft_strjoin(env_variables[i], env->value, 1);
			i++;
		}
		env = env->next;
	}
	env_variables[i] = NULL;
	return (env_variables);
}
