/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:13:15 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/05 19:44:56 by isalama          ###   ########.fr       */
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
			break;
		}
		env = env->next;
	}
	while (exec_paths[i])
	{
		if (access(ft_strjoin(exec_paths[i], content, 0), F_OK) == 0)
		{
			working_path = ft_strjoin(exec_paths[i], content, 0);
			return working_path;
			break;
		}
		i++;
	}
	return original_command;
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
		lets_pwd(*env);
	else if(ft_strcmp(commands->command, "exit") == 0)
		lets_exit();
	else if(ft_strcmp(commands->command, "echo") == 0)
		lets_echo(commands);
	else if(ft_strcmp(commands->command, "export") == 0 && commands->args[1])
		lets_export(env, commands->args);
	else if(ft_strcmp(commands->command, "env") == 0 || ft_strcmp(commands->command, "export") == 0)
		lets_env(*env);
	else if(ft_strcmp(commands->command, "unset") == 0)
		lets_unset(env, commands->args);
	return;
}


void execute_command(t_command *commands, t_env **env){
	int result;
	
	result = execve(get_function_path(commands->command, *env), commands->args, NULL);
	if(result == -1){
		printf("%s %s\n", ERROR_MSG_CMD_404, commands->command);
		exit(0);
	}
}


void tokens_execution(t_command *commands, t_env **env)
{
	pid_t	pid;
	int 	pipex[2];
	
	
	if(!commands->next && is_builtin(commands)){
		builtin_execution(commands, env);
		return;
	}

	int input = dup(STDIN_FILENO);
	int output = dup(STDOUT_FILENO);	
	while (commands)
	{
		pipe(pipex);
		pid = fork();
		if (pid == 0) {
			if (commands->next)
				dup2(pipex[1], STDOUT_FILENO);
			close(pipex[0]);
			
			if(commands->input != 0)
				dup2(commands->input, STDIN_FILENO);
			if(commands->output != 1)
				dup2(commands->output, STDOUT_FILENO);
			if (is_builtin(commands))
				builtin_execution(commands, env);
			else
				execute_command(commands, env);
			exit(0);
		} else {	
			dup2(pipex[0], STDIN_FILENO);
			close(pipex[1]);
			close(pipex[0]);
		}
		
	commands = commands->next;
	}
	while (wait(NULL) > 0);
	dup2(input, STDIN_FILENO);
	dup2(output, STDOUT_FILENO);
}