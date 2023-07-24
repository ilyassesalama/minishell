/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:13:15 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/24 15:24:15 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_function_path(char *content, t_env *env)
{
	char	*working_path;
	char	**exec_paths;
	int		i;

	i = 0;
	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0 && !env->is_hidden)
			break ;
		env = env->next;
	}
	if (!env)
		return (content);
	exec_paths = ft_split(env->value, ':');
	while (exec_paths[i] && !env->is_hidden)
	{
		working_path = ft_strjoin(exec_paths[i],
				ft_strjoin("/", content, 0), 0);
		if (access(working_path, F_OK) == 0)
			return (working_path);
		free(working_path);
		i++;
	}
	ft_free_array(exec_paths);
	return (content);
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

void	loop_through_commands(t_command *commands, t_env **env, int *pipex)
{
	while (commands)
	{
		if (is_non_dir(&commands))
			continue ;
		pipe(pipex);
		if (fork() == 0)
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
