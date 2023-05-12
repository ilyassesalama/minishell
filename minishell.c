/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:10:08 by isalama           #+#    #+#             */
/*   Updated: 2023/05/12 22:06:02 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void scan_input(char *input, t_data *data)
{
	if(!handle_quotes(input)){
		return;
	}
	t_token *tokens;
	tokens = tokens_creation(input);

	tokens_execution(tokens, data);
	
	ft_t_lstclear(&tokens);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_data *data;
	int i;
	char *receiver;
	char *input_command = "\033[1;31m➜ \033[1;32mminishell: \033[0m";
	char **path;

	i = 0;
	while (env[i] != NULL && ft_strcmp(env[i], "PATH=") != 0)
		i++;
	
	path = ft_split(ft_strchr(env[i], '='), ':');


	i = 0;
	while (path[i] != NULL)
	{
		ft_lstadd_back(&data, ft_lstnew(path[i]));
		i++;
	}
	
	while (true)
	{
		receiver = readline(input_command);
		if(receiver == NULL)
			break;
		if (ft_strlen(receiver) > 0) 
			add_history(receiver);
		scan_input(receiver, data);
	}
}
