/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:37:18 by isalama           #+#    #+#             */
/*   Updated: 2023/07/15 03:07:26 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	lets_exit(t_command *commands)
{
	if (commands->args[1] == NULL)
		exit(0);
	else if (commands->args[2])
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("exit: too many arguments\n", 2);
	}
	else if (commands->args[1] != NULL && ft_istrdigit(commands->args[1]))
		exit(ft_atoi(commands->args[1]));
	else
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("exit: fd: numeric argument required\n", 2);
		exit(255);
	}
}

void	lets_env(t_env *env, int fd)
{
	t_env	*envirement;

	envirement = env;
	while (envirement)
	{
		ft_putstr_fd(envirement->key, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(envirement->value, fd);
		ft_putstr_fd("\n", fd);
		envirement = envirement->next;
	}
}

void	lets_unset(t_env **env, char **args)
{
	t_env		*envirement;
	t_env		*prev;
	int			i;

	i = 1;
	envirement = *env;
	prev = NULL;
	while (envirement && args[i])
	{
		if (ft_strcmp(envirement->key, args[i]) == 0)
		{
			if (prev == NULL)
				*env = envirement->next;
			else
				prev->next = envirement->next;
			free(envirement->key);
			free(envirement->value);
			free(envirement);
			i++;
			envirement = *env;
		}
		prev = envirement;
		envirement = envirement->next;
	}
}
