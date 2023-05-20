/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:37:18 by isalama           #+#    #+#             */
/*   Updated: 2023/05/20 02:16:17 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_pwd()
{
	char path[PATH_MAX];
	if (getcwd(path, sizeof(path)) != NULL)
		printf("%s\n", path);
}

void ft_env(){
	
}

void ft_echo(t_token *tokens)
{
	while (tokens)
	{
		printf("%s ", tokens->content);
		tokens = tokens->next;
	}
	printf("\n");
}

void	ft_cd(t_command *commands, t_env *env)
{
	char	*home;
	char	*current_path = NULL;
	
	current_path = getcwd(current_path, sizeof(current_path));
	
	printf("current path: %s\n", current_path);
	if(ft_strcmp(current_path, "/") == 0){
		printf("Can't go anywhere, we're in the root directory\n");
		return;
	}
	
	if (commands->args[1] == NULL || (commands->args[1] && ft_strcmp(commands->args[1], "~") == 0)){
		printf("Going to home directory\n");
		home = get_env_value("HOME", env);
		if(!home){
			ft_putstr_fd("envirement error: HOME not set\n", 2);
			return;
		}
		if(chdir(home) == -1){
			ft_putstr_fd("No such file or directory\n", 2);
			return;
		}
		return;
	}
	
	if (commands->args[1] == NULL || (commands->args[1] && ft_strcmp(commands->args[1], "-") == 0)){
		printf("Going to old directory\n");
		home = get_env_value("OLDPWD", env);
		if(!home){
			ft_putstr_fd("envirement error: HOME not set\n", 2);
			return;
		}
		if(chdir(home) == -1){
			ft_putstr_fd("No such file or directory\n", 2);
			return;
		}
		return;
	}
	
	
	if (commands->args[1] && ft_strcmp(commands->args[1], "..") == 0){
		printf("Going to last directory\n");
		char*	last_slash = strrchr(current_path, '/');
		
		int		slash_size = 0;
		int		i = 0;
		while (current_path[i++])
			if (current_path[i] == '/')
				slash_size++;
		
		if(slash_size == 1){
			current_path = "/";
		}

		// if(ft_strlen(last_slash) == 6){
		// 	last_slash = ft_strchr(current_path, '/');
		// }
        if (last_slash != NULL) {
            *last_slash = '\0';
        }
		if (chdir(current_path) == -1)
		{
			ft_putstr_fd("No such file or directory\n", 2);
			return;
		}
		return;
	}
	
	printf("Going to specific directory\n");

	// if (chdir(tokens->next->content) == -1)
	// {
	// 	ft_putstr_fd("No such file or directory\n", 2);
	// 	return;
	// }
}
