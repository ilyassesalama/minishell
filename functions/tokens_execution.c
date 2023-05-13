/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:13:15 by tajjid            #+#    #+#             */
/*   Updated: 2023/05/13 23:18:30 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute(char *content, t_data *data)
{
	char *working_path = "";
	content = ft_strjoin("/", content, 0);
	while (data)
	{
		if (access(ft_strjoin(data->env_path, content, 0), F_OK) == 0)
		{
			working_path = ft_strjoin(data->env_path, content, 0);
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
		data = data->next;
	}
	return;
}


void ft_pwd()
{
	char path[PATH_MAX];
	if (getcwd(path, sizeof(path)) != NULL)
		printf("%s\n", path);
}


void ft_cd(t_token *tokens) {
	char path[PATH_MAX];

    if (getcwd(path, sizeof(path)) == NULL) {
        perror("getcwd() error");
        return;
    }
	if(tokens->next && (tokens->next->next->content == NULL || (tokens->next->next->content != NULL && (tokens->next->next->content[0] == '~' || tokens->next->next->content[0] == '\0')))){
		printf("Going to home directory.\n");
		if (chdir("/") == 0) {
			printf("Successfully moved to root directory.\n");
		}
		return;
	}
	
	printf("Going to last directory.\n");
	if (tokens->content[0] == '.' && tokens->content[1] == '.') {
		char* lastSlash = ft_strrchr(path, '/');

		if (lastSlash != NULL) {
			*lastSlash = '\0';
			if (chdir(path) == 0) {
				printf("Successfully moved to parent directory: %s\n", path);
			} else {
				perror("chdir() error");
			}
		} else {
			printf("Already at the root directory.\n");
		}
	}
	ft_pwd();
}


void ft_export(char *content)
{
	printf("export: %s\n", content);
}

void ft_unset(char *content)
{
	printf("unset: %s\n", content);
}

void ft_env(void)
{
	printf("env\n");
}

void ft_exit()
{
	exit(0);
}

void ft_single_q(char *content)
{
	printf("ft_single_q: %s\n", content);
}
void ft_double_q(char *content)
{
	printf("ft_double_q: %s\n", content);
}
void tokens_execution(t_token *tokens, t_data *data)
{
	t_token *tmp;
	(void)data;

	tmp = tokens;
	while (tmp)
	{
		if (ft_strcmp(tmp->content, "cd") == 0)
		{
			
			ft_cd(tmp);
		}
		else if (ft_strcmp(tmp->content, "pwd") == 0)
			ft_pwd();
		else if (ft_strcmp(tmp->content, "export") == 0)
			ft_export(tmp->content);
		else if (ft_strcmp(tmp->content, "unset") == 0)
			ft_unset(tmp->content);
		else if (ft_strcmp(tmp->content, "env") == 0)
			ft_env();
		else if (ft_strcmp(tmp->content, "exit") == 0)
			ft_exit();
		tmp = tmp->next;
	}
}