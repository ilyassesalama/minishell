/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:10:08 by isalama           #+#    #+#             */
/*   Updated: 2023/05/12 00:09:11 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct t_input_holder *input_holder;

void scan_input(char *input){	
	input_holder = ft_lstnew(input);
	
	handle_quotes(input);
	
}

int main(int argc, char **argv, char **env)
{
	int i;
	char *receiver;
	char *input_command = "\033[1;31m➜ \033[1;32mminishell: \033[0m";
	char **path;

	i = 0;
	while (env[i] != NULL && ft_strcmp(env[i], "PATH=") != 0)
		i++;
	path = ft_split(env[i], ':');
	while (true)
	{
		receiver = readline(input_command);
		if(receiver == NULL)
			break;
		if (ft_strlen(receiver) > 0) 
			add_history(receiver);
		scan_input(receiver);
	}
}
