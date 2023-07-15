/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:13:15 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/14 23:41:35 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *get_function_path(char *content, t_env *env)
{
	char *working_path = "";
	char **exec_paths = NULL;
	char *original_command = content;
	int i = 0;
	content = ft_strjoin("/", content, 0);
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 4) == 0)
		{
			exec_paths = ft_split(env->value, ':');
			break ;
		}
		env = env->next;
	}
	while (exec_paths[i])
	{
		if (access(ft_strjoin(exec_paths[i], content, 0), F_OK) == 0)
		{
			working_path = ft_strjoin(exec_paths[i], content, 0);
			return working_path;
			break ;
		}
		i++;
	}
	return (original_command);
}

bool	is_builtin(t_command *commands){
	char *builtins[] = {"cd", "pwd", "exit", "echo", "env", "export", "unset", NULL};
	int i = 0;
	while(builtins[i]){
		if(ft_strcmp(commands->command, builtins[i]) == 0)
			return true;
		i++;
	}
	return false;
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
	else if (ft_strcmp(commands->command, "env") == 0
		|| ft_strcmp(commands->command, "export") == 0)
		lets_env(*env, commands->output);
	else if (ft_strcmp(commands->command, "unset") == 0)
		lets_unset(env, commands->args);
	return ;
}

char **env_to_array(t_env *env){
	int i = 0;
	char **env_variables;
	t_env *tmp;
	
	tmp = env;
	while(tmp){
		i++;
		tmp = tmp->next;
	}
	env_variables = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env_variables)
		return NULL;
	i = 0;
	while(env){
		env_variables[i] = ft_strjoin(env->key, "=", 0);
		env_variables[i] = ft_strjoin(env_variables[i], env->value, 1);
		i++;
		env = env->next;
	}
	env_variables[i] = NULL;
	return env_variables;
}


void	execute_command(t_command *commands, t_env **env)
{
	int	result;
	char **env_variables;

	env_variables = env_to_array(*env);
	result = execve(get_function_path(commands->command, *env),
			commands->args, env_variables);
	if (commands->args[0] && result == -1)
	{
		ft_putstr_fd(ERROR_MSG_CMD_404, 2);
		exit(127);
	}
}

void set_to_default(int sig)
{
	(void)sig;
	return ;
}

void seg_set_to_default()
{
	signal(SIGINT, set_to_default);
	signal(SIGQUIT, set_to_default);
}

void tokens_execution(t_command *commands, t_env **env)
{
	pid_t   pid;
	int     pipex[2];
	int     status_code;

	if (!commands->next && is_builtin(commands))
	{
		builtin_execution(commands, env);
		return ;
	}

	int input = dup(STDIN_FILENO);
	int output = dup(STDOUT_FILENO);
	seg_set_to_default();
	while (commands)
	{
		pipe(pipex);
		pid = fork();
		if (pid == 0) {
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
		else
		{
			dup2(pipex[0], STDIN_FILENO);
			close(pipex[1]);
			close(pipex[0]);
		}
		commands = commands->next;
	}

	while (waitpid(-1, &status_code, 0) != -1);
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
