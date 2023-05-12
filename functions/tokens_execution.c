/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_execution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 19:13:15 by tajjid            #+#    #+#             */
/*   Updated: 2023/05/12 22:24:40 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(char *content, t_data *data)
{

	char *working_path = "";
	content = ft_strjoin("/", content, 0);
	while(data){
		if (access(ft_strjoin(data->env_path, content, 0), F_OK) == 0)
		{
			working_path = ft_strjoin(data->env_path, content, 0);
			pid_t pid = fork();
			char *argv[] = {"ls", NULL};
        	if(pid == 0) {
				execve(working_path, argv, NULL);
				perror("execve");
        		exit(EXIT_FAILURE);
			}
			wait(NULL);			break;
		}
		data = data->next;
	}
	return ;
}


void	ft_cd(char *content)
{
	printf("cd: %s\n", content);
}

void	ft_pwd(void)
{
	printf("pwd\n");
}

void	ft_export(char *content)
{
	printf("export: %s\n", content);
}

void	ft_unset(char *content)
{
	printf("unset: %s\n", content);
}

void	ft_env(void)
{
	printf("env\n");
}

void	ft_exit(char *content)
{
	printf("exit: %s\n", content);
}

void	ft_single_q(char *content)
{
	printf("ft_single_q: %s\n", content);
}
void	ft_double_q(char *content)
{
	printf("ft_double_q: %s\n", content);
}
void	tokens_execution(t_token *tokens, t_data *data)
{
	t_token *tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp -> type == 1)
			execute(tmp -> content, data);
		else if (tmp -> type == 2)
			ft_cd(tmp -> content);
		else if (tmp -> type == 3)
			ft_pwd();
		else if (tmp -> type == 4)
			ft_export(tmp -> content);
		else if (tmp -> type == 5)
			ft_unset(tmp -> content);
		else if (tmp -> type == 6)
			ft_env();
		else if (tmp -> type == 7)
			ft_exit(tmp -> content);
		else if (tmp -> type == 8)
			ft_single_q(tmp -> content);
		else if (tmp -> type == 9)
			ft_double_q(tmp -> content);
		tmp = tmp -> next;
	}
}