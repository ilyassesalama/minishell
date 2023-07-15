/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:37:18 by isalama           #+#    #+#             */
/*   Updated: 2023/07/15 02:58:46 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	lets_pwd(t_env *env, int fd)
{
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)) != NULL)
	{
		ft_putstr_fd(path, fd);
		ft_putstr_fd("\n", fd);
	}
	else
	{
		ft_putstr_fd(get_env_value("PWD", env), fd);
		ft_putstr_fd("\n", fd);
	}
}

void	lets_echo(t_command *commands)
{
	bool	is_n;
	int		i;

	if (commands->args[1] && ft_strcmp(commands->args[1], "-n") == 0)
		is_n = true;
	else
		is_n = false;
	if (is_n)
		i = 2;
	else
		i = 1;
	while (commands->args[i])
	{
		ft_putstr_fd(commands->args[i], commands->output);
		if (commands->args[i + 1])
			ft_putstr_fd(" ", commands->output);
		i++;
	}
	if (!is_n)
		ft_putstr_fd("\n", commands->output);
	g_global.exit_status = 0;
}

void	lets_cd(t_command *commands, t_env *env)
{
	char	*home;

	home = NULL;
	if (commands->args[1] == NULL || (!ft_strcmp(commands->args[1], "~")))
	{
		home = get_env_value("HOME", env);
		if (!home)
		{
			ft_putstr_fd(ERROR_MSG_ENV, 2);
			return ;
		}
		else
			if (chdir(home) == -1)
				ft_putstr_fd(ERROR_MSG_NOFILE, 2);
	}
	else
		if (chdir(commands->args[1]) == -1)
			ft_putstr_fd(ERROR_MSG_NOFILE, 2);
	update_env("OLDPWD", get_env_value("PWD", env), env);
	update_env("PWD", get_current_path(env), env);
}
