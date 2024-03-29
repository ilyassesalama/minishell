/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 03:26:41 by isalama           #+#    #+#             */
/*   Updated: 2023/07/25 18:29:54 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	lets_print_export(t_env *env, int output)
{
	t_env	*env_tmp;

	env_tmp = env;
	while (env_tmp)
	{
		if (!env_tmp->is_hidden)
		{
			ft_putstr_fd("declare -x ", output);
			ft_putstr_fd(env_tmp->key, output);
			if (env_tmp->value)
			{
				ft_putstr_fd("=\"", output);
				ft_putstr_fd(env_tmp->value, output);
				ft_putstr_fd("\"", output);
			}
			ft_putstr_fd("\n", output);
		}
		env_tmp = env_tmp->next;
	}
}

void	builtin_execution(t_command *commands, t_env **env)
{
	if (ft_strcmp(commands->command, "cd") == 0)
		g_global.exit_status = lets_cd(commands, *env);
	else if (ft_strcmp(commands->command, "pwd") == 0)
		g_global.exit_status = lets_pwd(*env, commands->output);
	else if (ft_strcmp(commands->command, "exit") == 0)
		lets_exit(commands);
	else if (ft_strcmp(commands->command, "echo") == 0)
		g_global.exit_status = lets_echo(commands);
	else if (ft_strcmp(commands->command, "export") == 0 && commands->args[1])
		lets_export(env, commands->args);
	else if (ft_strcmp(commands->command, "env") == 0)
		g_global.exit_status = lets_env(*env, commands->output);
	else if (ft_strcmp(commands->command, "export") == 0)
		lets_print_export(*env, commands->output);
	else if (ft_strcmp(commands->command, "unset") == 0)
		lets_unset(env, commands->args);
	return ;
}
