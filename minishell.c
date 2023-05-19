/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:10:08 by isalama           #+#    #+#             */
/*   Updated: 2023/05/19 21:04:17 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void scan_input(char *input, t_env *env)
{
	if(!handle_quotes(input)){
		return;
	}
	
	t_token *tokens;
	tokens = tokens_creation(input);
	if (tokens == NULL)
		return ;
	//t_token *temp = tokens;
	tokens_execution(tokens, env);
	// while (temp != NULL)
	// {
	// 	printf("token: %s type: %d\n ", temp->content, temp->type);
	// 	temp = temp->next;
	// }
	// ft_t_lstclear(&tokens);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_env *env_list;
	int i;
	char *receiver;
	char *input_command = "\033[1;31m➜ \033[1;32m minishell: \033[0m";

	i = 0;
	while (env[i] != NULL && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	
	i = 0;
	while (env[i] != NULL)
	{
		char **temp = ft_split(env[i], '=');
		ft_lstadd_back(&env_list, ft_envlstnew(ft_strdup(temp[0]), ft_strdup(temp[1])));
		i++;
	}
	
	while (true)
	{
		receiver = readline(input_command);
		if(receiver == NULL)
			break;
		if (ft_strlen(receiver) > 0) 
			add_history(receiver);
		scan_input(receiver, env_list);
	}
}
