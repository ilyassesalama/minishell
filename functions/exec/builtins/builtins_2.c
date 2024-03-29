/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:37:18 by isalama           #+#    #+#             */
/*   Updated: 2023/07/28 16:23:48 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	lets_exit_2(t_command *commands, int args_size)
{
	if (!ft_istrnegdigit(commands->args[1])
		&& ft_istrnegdigit(commands->args[args_size - 1]))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		exit(255);
	}
	if (args_size > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		g_global.exit_status = 1;
		return ;
	}
	else if ((commands->args[1][0] == '-' && ft_strlen(commands->args[1]) > 20)
			|| (commands->args[1][0] != '-'
			&& ft_strlen(commands->args[1]) > 19))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		exit(255);
	}
	if (commands->args[1][0] == '-')
		exit((ft_atoi(commands->args[1])) + 256);
	exit(ft_atoi(commands->args[1]));
}

void	lets_exit(t_command *commands)
{
	int	args_size;

	args_size = ft_arrsize(commands->args);
	ft_putstr_fd("exit\n", 2);
	if (args_size <= 1)
		exit(0);
	if (commands->args[1][0] == '\0')
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		exit(255);
	}
	if (!ft_istrnegdigit(commands->args[1]))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		exit(255);
	}
	if (!ft_istrnegdigit(commands->args[1])
		&& !ft_istrnegdigit(commands->args[args_size - 1]))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		exit(255);
	}
	lets_exit_2(commands, args_size);
}

int	lets_env(t_env *env, int fd)
{
	t_env	*env_tmp;

	env_tmp = env;
	while (env_tmp)
	{
		if (!env_tmp->is_hidden)
		{
			if (env_tmp->key && env_tmp->value)
				ft_putstr_fd(env_tmp->key, fd);
			if (env_tmp->value && ft_strlen(env_tmp->value) >= 0)
			{
				ft_putstr_fd("=", fd);
				ft_putstr_fd(env_tmp->value, fd);
				ft_putstr_fd("\n", fd);
			}
		}
		env_tmp = env_tmp->next;
	}
	return (0);
}

void	lets_unset_rest(t_env **env, char **args, int i)
{
	t_env	*tmp;

	tmp = *env;
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

void	lets_unset(t_env **env, char **args)
{
	int		i;

	i = 1;
	while (args[i])
	{
		if (is_exportable(args[i]))
			lets_unset_rest(env, args, i);
		else
		{
			ft_putstr_fd(ERROR_MSG_IDENTIFIER, 2);
			g_global.exit_status = 1;
		}
		i++;
	}
	g_global.exit_status = 0;
}
