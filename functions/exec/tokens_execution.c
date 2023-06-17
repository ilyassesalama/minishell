/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:13:15 by tajjid            #+#    #+#             */
/*   Updated: 2023/06/18 00:13:40 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void execute(char *content, t_env *env, char **args)
{
	char *working_path = "";
	char **exec_paths = NULL;
	int i = 0;
	content = ft_strjoin("/", content, 0);
	int exit_status = 0;
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 4) == 0)
		{
			exec_paths = ft_split(env->value, ':');
			break;
		}
		env = env->next;
	}
	while (exec_paths[i])
	{
		if (access(ft_strjoin(exec_paths[i], content, 0), F_OK) == 0)
		{
			working_path = ft_strjoin(exec_paths[i], content, 0);
			pid_t pid = fork();
			if (pid == 0)
			{
				execve(working_path, args, NULL);
				perror("execve");
				exit(125);
			}
			wait(&exit_status);
			break;
		}
		i++;
	}
	execve("ls", args, NULL);
	return;
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

void builtin_execution(t_command *commands, t_env **env){
	if(ft_strcmp(commands->command, "cd") == 0)
		lets_cd(commands, *env);
	else if(ft_strcmp(commands->command, "pwd") == 0)
		lets_pwd();
	else if(ft_strcmp(commands->command, "exit") == 0)
		lets_exit();
	else if(ft_strcmp(commands->command, "echo") == 0)
		lets_echo(commands);
	else if(ft_strcmp(commands->command, "env") == 0)
		lets_env(*env);
	else if(ft_strcmp(commands->command, "export") == 0)
		lets_export(*env, commands->args);
	else if(ft_strcmp(commands->command, "unset") == 0)
		lets_unset(env, commands->args);
	return;
}

void tokens_execution(t_command *commands, t_env *env)
{
	pid_t	pid;
	int 	pipex[2];

	int input = dup(STDIN_FILENO);
	int output = dup(STDOUT_FILENO);	
	while (commands)
	{
		pipe(pipex);
		pid = fork();
		if (pid == 0)
		{
			if (commands->next)
				dup2(pipex[1], 1);
			close(pipex[0]);
			if (is_builtin(commands))
			{
				builtin_execution(commands, &env);
				exit(0);
			} else 
				execve(commands->command, commands->args, NULL);
		}
		else
		{	
			dup2(pipex[0], 0);
			close(pipex[1]);
			close(pipex[0]);
		}
		commands = commands->next;
		
	}
	while (wait(NULL) > 0);
	dup2(input, STDIN_FILENO);
	dup2(output, STDOUT_FILENO);
}
