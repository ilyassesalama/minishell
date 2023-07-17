/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:37:18 by isalama           #+#    #+#             */
/*   Updated: 2023/07/17 05:40:53 by isalama          ###   ########.fr       */
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

bool	lets_echo_rest(char **str, int *i, int *j, int *is_n)
{
	if (str[*i][*j] == '-')
	{
		(*j)++;
		while (str[*i][*j])
		{
			if (str[*i][*j] != 'n')
			{
				is_n = false;
				break ;
			}
			(*j)++;
		}
	}
	else
		return (false);
	if (!is_n)
		return (false);
	return (true);
}

void	lets_echo(t_command *commands)
{
	int	is_n;
	int	i;
	int	j;

	i = 1;
	j = 0;
	is_n = true;
	while (commands->args[i])
	{
		j = 0;
		if (!lets_echo_rest(commands->args, &i, &j, &is_n))
			break ;
		i++;
	}
	is_n = i;
	while (commands->args[i])
	{
		ft_putstr_fd(commands->args[i], commands->output);
		if (commands->args[i + 1])
			ft_putstr_fd(" ", commands->output);
		i++;
	}
	if (is_n == 1)
		ft_putstr_fd("\n", commands->output);
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
	update_env("OLDPWD", ft_strdup(get_env_value("PWD", env)), env);
	update_env("PWD", get_current_path(env), env);
}
