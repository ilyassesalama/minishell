/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 03:26:41 by isalama           #+#    #+#             */
/*   Updated: 2023/07/18 07:32:45 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	lets_print_export(t_env *env)
{
	t_env	*env_tmp;

	env_tmp = env;
	while (env_tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env_tmp->key, 1);
		if (env_tmp->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env_tmp->value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		env_tmp = env_tmp->next;
	}
}

void	builtin_execution(t_command *commands, t_env **env)
{
	if (ft_strcmp(commands->command, "cd") == 0)
		lets_cd(commands, *env);
	else if (ft_strcmp(commands->command, "pwd") == 0)
		lets_pwd(*env, commands->output);
	else if (ft_strcmp(commands->command, "exit") == 0)
		lets_exit(commands);
	else if (ft_strcmp(commands->command, "echo") == 0)
		lets_echo(commands);
	else if (ft_strcmp(commands->command, "export") == 0 && commands->args[1])
		lets_export(env, commands->args);
	else if (ft_strcmp(commands->command, "env") == 0)
		lets_env(*env, commands->output);
	else if (ft_strcmp(commands->command, "export") == 0)
		lets_print_export(*env);
	else if (ft_strcmp(commands->command, "unset") == 0)
		lets_unset(env, commands->args);
	return ;
}
