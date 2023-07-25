/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:13:15 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/25 17:15:35 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_exit_status(int input, int output)
{
	int	status_code;

	while (waitpid(-1, &status_code, 0) != -1)
		;
	if (WIFSIGNALED(status_code))
	{
		if (WTERMSIG(status_code) == SIGINT)
		{
			g_global.exit_status = 130;
			ft_putstr_fd("\n", 2);
		}
		else if (WTERMSIG(status_code) == SIGQUIT)
		{
			g_global.exit_status = 131;
			ft_putstr_fd("Quit: 3\n", 2);
		}
	}
	else if (WIFEXITED(status_code))
		g_global.exit_status = WEXITSTATUS(status_code);
	dup2(input, STDIN_FILENO);
	dup2(output, STDOUT_FILENO);
}

void	execute_command(t_command *commands, t_env **env)
{
	int		result;
	char	**env_variables;

	env_variables = env_to_array(*env);
	if (commands->command[0] == '/' || commands->command[0] == '.')
	{
		result = execve(commands->command,
				commands->args, env_variables);
	}
	else
	{
		result = execve(get_function_path(commands->command, *env),
				commands->args, env_variables);
	}
	if (commands->args[0] && result == -1)
	{
		ft_putstr_fd(ERROR_MSG_CMD_404, 2);
		ft_putstr_fd(commands->args[0], 2);
		ft_putstr_fd("\n", 2);
		exit(127);
	}
	ft_free_array(env_variables);
}

void	init_execution(t_command *commands, t_env **env, int *pipex)
{
	if (commands->next)
		dup2(pipex[1], STDOUT_FILENO);
	close(pipex[0]);
	if (commands->input != 0)
		dup2(commands->input, STDIN_FILENO);
	if (commands->output != 1)
		dup2(commands->output, STDOUT_FILENO);
	if (is_builtin(commands))
		builtin_execution(commands, env);
	else
		execute_command(commands, env);
	exit(0);
}

void	loop_through_commands(t_command *commands, t_env **env, int *pipex)
{
	pid_t	pid;

	while (commands)
	{
		if (is_non_dir(&commands))
			continue ;
		if (pipe(pipex) == -1)
		{
			ft_putstr_fd(ERROR_PIPE, 2);
			break ;
		}
		pid = fork();
		if (pid == -1)
		{
			ft_putstr_fd(ERROR_FORK, 2);
			break ;
		}
		else if (pid == 0)
			init_execution(commands, env, pipex);
		dup2(pipex[0], STDIN_FILENO);
		close_resources(commands, pipex);
		commands = commands->next;
	}
}

void	tokens_execution(t_command *commands, t_env **env)
{
	int		pipex[2];
	int		input;
	int		output;

	if (!commands)
		return ;
	if (!commands->next && is_builtin(commands))
	{
		builtin_execution(commands, env);
		return ;
	}
	input = dup(STDIN_FILENO);
	output = dup(STDOUT_FILENO);
	invalidate_signals();
	loop_through_commands(commands, env, pipex);
	handle_exit_status(input, output);
	close(input);
	close(output);
}
