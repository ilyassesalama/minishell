/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 20:11:11 by isalama           #+#    #+#             */
/*   Updated: 2023/07/25 17:07:56 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_function_path(char *content, t_env *env)
{
	char	*working_path;
	char	**exec_paths;
	int		i;

	i = 0;
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0 && !env->is_hidden)
			break ;
		env = env->next;
	}
	if (!env)
		return (content);
	exec_paths = ft_split(env->value, ':');
	while (exec_paths[i] && !env->is_hidden)
	{
		working_path = ft_strjoin(exec_paths[i],
				ft_strjoin("/", content, 0), 0);
		if (access(working_path, F_OK) == 0)
			return (working_path);
		free(working_path);
		i++;
	}
	ft_free_array(exec_paths);
	return (content);
}
