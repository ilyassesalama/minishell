/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:37:18 by isalama           #+#    #+#             */
/*   Updated: 2023/05/19 21:47:27 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_pwd()
{
	char path[PATH_MAX];
	if (getcwd(path, sizeof(path)) != NULL)
		printf("%s\n", path);
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

char *get_env_value(char *key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}


void ft_cd(t_token *tokens, t_env *env) {
	char *home;
	
	home = get_env_value("HOME", env);
	if(!home){
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return;
	}
	//printf("cd right now..\n");
	int i = 0;
	while(tokens)
	{
		printf("%d ->", i++);
		printf("%s\n", tokens->content);
		tokens = tokens->next;
	}
	(void)env;
	// char *home;

	// if (tokens->next == NULL)
	// {
	// 	if ((home = get_env_value("HOME", env)) == NULL)
	// 	{
	// 		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	// 		return ;
	// 	}
	// 	if (chdir(home) == -1)
	// 	{
	// 		ft_putstr_fd("minishell: cd: ", 2);
	// 		ft_putstr_fd(home, 2);
	// 		ft_putstr_fd(": ", 2);
	// 		ft_putstr_fd("Error", 2);
	// 		ft_putstr_fd("\n", 2);
	// 	}
	// }
	// else
	// {
	// 	if (chdir(tokens->next->content) == -1)
	// 	{
	// 		ft_putstr_fd("minishell: cd: ", 2);
	// 		ft_putstr_fd(tokens->next->content, 2);
	// 		ft_putstr_fd(": ", 2);
	// 		ft_putstr_fd("", 2);
	// 		ft_putstr_fd("\n", 2);
	// 	}
	// }
}