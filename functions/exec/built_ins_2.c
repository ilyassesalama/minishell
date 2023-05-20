/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:37:18 by isalama           #+#    #+#             */
/*   Updated: 2023/05/20 03:46:46 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	lets_exit(void)
{
	exit(0);
}

void	lets_env(t_env *env)
{
	t_env	*envirement;

	envirement = env;
	while (envirement)
	{
		ft_putstr_fd(envirement->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(envirement->value, 1);
		ft_putstr_fd("\n", 1);
		envirement = envirement->next;
	}
}

void	lets_export(t_env *env, char **args)
{
	t_env		*envirement;
	bool		already_there;

	already_there = false;
	envirement = env;
	while (envirement)
	{
		if (ft_strcmp(envirement->key, args[1]) == 0)
		{
			already_there = true;
			break ;
		}
		envirement = envirement->next;
	}
	if (!already_there)
		ft_lstadd_back(&env,
			ft_envlstnew(ft_strdup(args[1]), ft_strdup(args[2])));
}

void	lets_unset(t_env **env, char **args)
{
	t_env		*envirement;
	t_env		*prev;

	envirement = *env;
	prev = NULL;
	while (envirement)
	{
		if (ft_strcmp(envirement->key, args[1]) == 0)
		{
			if (prev == NULL)
				*env = envirement->next;
			else
				prev->next = envirement->next;
			free(envirement->key);
			free(envirement->value);
			free(envirement);
			break ;
		}
		prev = envirement;
		envirement = envirement->next;
	}
}
