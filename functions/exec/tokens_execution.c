/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:13:15 by tajjid            #+#    #+#             */
/*   Updated: 2023/05/20 03:48:01 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void execute(char *content, t_env *env)
{
	char *working_path = "";
	char **exec_paths = NULL;
	int i = 0;
	content = ft_strjoin("/", content, 0);
	
	while(env)
	{
		if (ft_strncmp(env->key, "PATH", 4) == 0){
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
			char *argv[] = {"-la", NULL};
			if (pid == 0)
			{
				execve(working_path, argv, NULL);
				perror("execve");
				exit(EXIT_FAILURE);
			}
			wait(NULL);
			break;
		}
		i++;
	}
	return;
}

void tokens_execution(t_env *env)
{
	t_command *commands = NULL;
	//command_add_back(&commands, command_lstnew("export", (char*[]){"export", "key", "hello world", NULL}, 0, 0));
	//command_add_back(&commands, command_lstnew("unset", (char*[]){"unset", "hello", "hello world", NULL}, 0, 0));
	command_add_back(&commands, command_lstnew("env", (char*[]){"/usr/bin/env", NULL}, 0, 0));
	while (commands)
	{
		if (ft_strcmp(commands->command, "cd") == 0)
			lets_cd(commands, env);
		else if (ft_strcmp(commands->command, "pwd") == 0)
			lets_pwd();
		else if (ft_strcmp(commands->command, "exit") == 0)
			lets_exit();
		else if (ft_strcmp(commands->command, "echo") == 0)
			lets_echo(commands);
		else if (ft_strcmp(commands->command, "env") == 0)
			lets_env(env);
		else if (ft_strcmp(commands->command, "export") == 0)
			lets_export(env, commands->args);
		else if (ft_strcmp(commands->command, "unset") == 0)
			lets_unset(&env, commands->args);
		else
			execute(commands->command, env);
		commands = commands->next;
	}
}