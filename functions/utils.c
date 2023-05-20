/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 21:58:43 by isalama           #+#    #+#             */
/*   Updated: 2023/05/19 23:08:38 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

char* get_current_dir(char* path) {
	char* last_slash = NULL;
	last_slash = ft_strrchr(path, '/');
    if (last_slash != NULL) 
        last_slash += 1;
	return last_slash;
}

char *get_env_value(char *key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}