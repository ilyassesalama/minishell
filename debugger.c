/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugger.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 02:32:27 by isalama           #+#    #+#             */
/*   Updated: 2023/07/17 02:51:39 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_commands(t_command *commands)
{
	int	i;

	i = 0;
	while (commands)
	{
		printf("------------------------------------\n");
		printf("command: %s\n", commands -> command);
		printf("input: %d\n", commands -> input);
		printf("output: %d\n", commands -> output);
		while (commands -> args[i])
		{
			printf("arg[%d] : %s\n", i, commands -> args[i]);
			i++;
		}
		i = 0;
		commands = commands -> next;
		printf("------------------------------------\n");
	}
}

void	print_tokens(t_token *tokens)
{
	printf("------------------------------------\n");
	while (tokens)
	{
		printf("token: %s  type: %d\n", tokens -> content, tokens -> type);
		tokens = tokens -> next;
	}
	printf("------------------------------------\n");
}
void	init_debugger(t_command *commands, t_token *tokens)
{
	printf("\n\033[0;34mCommands output:\033[0m\n");
	print_commands(commands);
	printf("\n\033[0;34mTokens output:\033[0m\n");
	print_tokens(tokens);
	printf("\n");
}
