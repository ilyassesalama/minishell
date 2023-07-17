/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 03:26:41 by isalama           #+#    #+#             */
/*   Updated: 2023/07/17 00:33:00 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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
	else if (ft_strcmp(commands->command, "env") == 0
		|| ft_strcmp(commands->command, "export") == 0)
		lets_env(*env, commands->output);
	else if (ft_strcmp(commands->command, "unset") == 0)
		lets_unset(env, commands->args);
	return ;
}
