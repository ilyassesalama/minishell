/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:11:11 by isalama           #+#    #+#             */
/*   Updated: 2023/07/15 04:12:44 by isalama          ###   ########.fr       */
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
	return (get_env_value("PWD", env));
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
			temp->value = ft_strdup(value);
			return ;
		}
		temp = temp->next;
	}
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

char	**env_to_array(t_env *env)
{
	int		i;
	char	**env_variables;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	env_variables = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env_variables)
		return (NULL);
	i = 0;
	while (env)
	{
		env_variables[i] = ft_strjoin(env->key, "=", 0);
		env_variables[i] = ft_strjoin(env_variables[i], env->value, 1);
		i++;
		env = env->next;
	}
	env_variables[i] = NULL;
	return (env_variables);
}
