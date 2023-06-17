/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:37:18 by isalama           #+#    #+#             */
/*   Updated: 2023/06/11 15:23:37 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	lets_pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)) != NULL)
		printf("%s\n", path);
}

int getLastExitCode() {
	return 0;
}

void	lets_echo(t_command *commands)
{
	bool	is_n;

	is_n = (commands->args[1] && ft_strcmp(commands->args[1], "-n") == 0);

	int i = 1;
	if (is_n)
		i++;
	while(commands->args[i]){
		if (ft_strcmp(commands->args[i], "$?") == 0){
			ft_putnbr_fd(getLastExitCode(), 1);
		} else {
			ft_putstr_fd(commands->args[i], 1);
		}
		i++;
	}
	if (!is_n)
		ft_putstr_fd("\n", 1);
}

void	lets_cd(t_command *commands, t_env *env)
{
	char	*home;
	char	*current_path;

	current_path = get_current_path();
	if (ft_strcmp(current_path, "/") == 0)
		return ;
	if (commands->args[1] == NULL || (commands->args[1]
			&& ft_strcmp(commands->args[1], "~") == 0))
	{
		home = get_env_value("HOME", env);
		if (!home)
			return (ft_putstr_fd(ERROR_MSG_ENV, 2));
		if (chdir(home) == -1) {
			ft_putstr_fd(ERROR_MSG_INV_PATH, 2);
			return ;
		}
		update_env("PWD", get_current_path(), env);
		return ;
	}
	if (commands->args[1] || chdir(commands->args[1]) == -1)
		ft_putstr_fd(ERROR_MSG_INV_PATH, 2);
		
	update_env("PWD", get_current_path(), env);
}
