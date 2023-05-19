/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:13:15 by tajjid            #+#    #+#             */
/*   Updated: 2023/05/19 21:05:59 by isalama          ###   ########.fr       */
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
			char *argv[] = {"ls", NULL};
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

void tokens_execution(t_token *tokens, t_env *env)
{
	while (tokens)
	{
		if (ft_strcmp(tokens->content, "cd") == 0)
			ft_cd(tokens, env);
		else if (ft_strcmp(tokens->content, "pwd") == 0)
			ft_pwd();
		else if (ft_strcmp(tokens->content, "exit") == 0)
			ft_exit();
		else
			execute(tokens->content, env);
		tokens = tokens->next;
	}
}