/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:37:18 by isalama           #+#    #+#             */
/*   Updated: 2023/07/14 02:22:18 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	lets_pwd(t_env *env)
{
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)) != NULL)
		printf("%s\n", path);
	else
		printf("%s\n", get_env_value("PWD", env));
}

void	lets_echo(t_command *commands)
{
	bool	is_n = true;
	t_command *cmd_tmp = commands;

	is_n = (commands->args[1] && ft_strcmp(commands->args[1], "-n") == 0);
	
		int i = 1;
		int j = 0;
		while(cmd_tmp->args[i])
		{
			j = 0;
			if(cmd_tmp->args[i][j] == '-')
			{
				j++;
				while (cmd_tmp->args[i][j])
				{
					if(cmd_tmp->args[i][j] != 'n')
					{
						is_n = false;
						break;
					}
					j++;
				}
			}
			else
				break;
			if (!is_n)
				break;
			i++;
		}
	is_n = i == 1 ? true : false;
	while (cmd_tmp->args[i])
	{
		ft_putstr_fd(cmd_tmp->args[i], commands->output);
		if (cmd_tmp->args[i + 1])
			ft_putstr_fd(" ", commands->output);
		i++;
	}
	if (is_n)
		ft_putstr_fd("\n", commands->output);
	
	// printf("%d\n", g_global.exit_status);
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
		else
			if (chdir(commands->args[1]) == -1)
				ft_putstr_fd(ERROR_MSG_NOFILE, 2);
	}
	update_env("OLDPWD", get_env_value("PWD", env), env);
	update_env("PWD", get_current_path(env), env);
}
