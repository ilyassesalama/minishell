/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:04:45 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/17 01:58:37 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define ARE_WE_EXECUTING false

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("token: %s  type: %d\n", tokens -> content, tokens -> type);
		tokens = tokens -> next;
	}
}

// void	print_commands(t_command *commands)
// {
// 	int	i;

// 	i = 0;
// 	while (commands)
// 	{
// 		printf("------------------------------------\n");
// 		printf("command: %s\n", commands -> command);
// 		printf("input: %d\n", commands -> input);
// 		printf("output: %d\n", commands -> output);
// 		while (commands -> args[i])
// 		{
// 			printf("arg[%d] : %s\n", i, commands -> args[i]);
// 			i++;
// 		}
// 		i = 0;
// 		commands = commands -> next;
// 		printf("------------------------------------\n");
// 	}
// }

void	scan_input(char *input, t_env **env)
{
	int			i;
	t_token		*tokens;
	t_command	*commands;

	i = 0;
	if (!handle_quotes(input))
		return ;
	tokens = tokens_creation(input, *env);
	if (tokens == NULL)
		return ;
	// print_tokens(tokens);
	commands = command_creator(tokens, *env);
	if (ARE_WE_EXECUTING)
		tokens_execution(commands, env);
	else
		print_commands(commands);
	ft_t_lstclear(&tokens);
	ft_c_lstclear(&commands);
}

int	main(int argc, char **argv, char **env)
{
	t_env	*env_list;
	int		i;
	char	*receiver;
	char	*input_command;
	char	**temp;

	if (argc != 1)
		return (0);
	signals_handler();
	rl_catch_signals = 0;
	g_global.heredoc_eof = 0;
	input_command = "\x1b[32m minishell: \x1b[0m";
	(void)argc;
	(void)argv;
	i = 0;
	while (env[i] != NULL && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	i = 0;
	while (env[i] != NULL)
	{
		temp = ft_split(env[i], '=');
		ft_lstadd_back(&env_list,
			ft_envlstnew(ft_strdup(temp[0]), ft_strdup(temp[1])));
		i++;
	}
	while (true)
	{
		signals_handler();
		g_global.heredoc_eof = 0;
		receiver = readline(input_command);
		if (receiver == NULL)
			break ;
		if (ft_strlen(receiver) > 0)
			add_history(receiver);
		scan_input(receiver, &env_list);
		signals_handler();
	}
}
