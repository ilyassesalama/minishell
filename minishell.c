/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:04:45 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/11 17:18:39 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define ARE_WE_EXECUTING true

void	scan_input(char *input, t_env **env)
{
	int			i = 0;
	t_token		*tokens;
	t_command		*commands;

	if (!handle_quotes(input))
		return ;
	tokens = tokens_creation(input, *env);
	if (tokens == NULL)
		return ;
	commands = command_creator(tokens);
	if (ARE_WE_EXECUTING)
		tokens_execution(commands, env);
	else
	{
		while (commands)
		{
			i = 0;
			printf("--------------------\n");
			printf("{ command: %s input: %d output: %d }\n", commands->command, commands->input, commands->output);
			while (commands->args[i])
			{
				printf("arg: %s\n", commands->args[i]);
				i++;
			}
			printf("--------------------\n");
			commands = commands->next;
		}
	}
	ft_t_lstclear(&tokens);
	ft_c_lstclear(&commands);
}

int	main(int argc, char **argv, char **env)
{
	t_env	*env_list;
	int		i;
	char	*receiver;
	char	*input_command;

	input_command = "\x1b[32m minishell: \x1b[0m";
	(void)argc;
	(void)argv;
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
		if (receiver == NULL)
			break ;
		if (ft_strlen(receiver) > 0)
			add_history(receiver);
		scan_input(receiver, &env_list);
	}
}
