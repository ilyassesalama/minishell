/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:37:18 by isalama           #+#    #+#             */
/*   Updated: 2023/07/24 11:59:13 by isalama          ###   ########.fr       */
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
		exit(1);
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
	t_env	*env_tmp;

	env_tmp = env;
	while (env_tmp)
	{
		if (env_tmp->value && ft_strlen(env_tmp->value) > 0
			&& !env_tmp->is_hidden)
		{
			ft_putstr_fd(env_tmp->key, fd);
			ft_putstr_fd("=", fd);
			ft_putstr_fd(env_tmp->value, fd);
			ft_putstr_fd("\n", fd);
		}
		env_tmp = env_tmp->next;
	}
}

void	lets_unset(t_env **env, char **args)
{
	int		i;
	t_env	*tmp;

	i = 1;
	while (args[i])
	{
		tmp = *env;
		if (is_exportable(args[i]))
		{
			while (tmp)
			{
				if (ft_strcmp(tmp->key, args[i]) == 0 && !tmp->is_hidden)
				{
					tmp->is_hidden = true;
					break ;
				}
				tmp = tmp->next;
			}
		}
		else if (ft_strlen(args[i]) > 0)
			ft_putstr_fd(ERROR_MSG_IDENTIFIER, 2);
		i++;
	}
}
