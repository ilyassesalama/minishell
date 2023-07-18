/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:04:45 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/18 08:27:37 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	commands = command_creator(tokens, *env);
	if (ARE_WE_DEBUGGING)
	{
		printf("\033[0;34mExecution output:\033[0m\n");
		printf("------------------------------------\n");
	}
	if (ARE_WE_DEBUGGING)
	{
		printf("------------------------------------\n");
		init_debugger(commands, tokens);
	}
	ft_t_lstclear(&tokens);
	tokens_execution(commands, env);
	ft_c_lstclear(&commands);
}

void	init_readline(t_env **env_list)
{
	int		i;
	char	*receiver;

	i = 0;
	while (true)
	{
		signals_handler();
		g_global.heredoc_eof = 0;
		receiver = readline("\001\033[32m\002 minishell:\001\033[0m\002 ");
		if (receiver == NULL)
			break ;
		if (ft_strlen(receiver) > 0)
			add_history(receiver);
		scan_input(receiver, env_list);
		signals_handler();
		free(receiver);
	}
}

int	main(int argc, char **argv, char **env)
{
	int		i;
	char	**temp;
	t_env	*env_list;

	env_list = NULL;
	i = 0;
	if (argc != 1)
		return (1);
	signals_handler();
	rl_catch_signals = 0;
	g_global.heredoc_eof = 0;
	(void)argc;
	(void)argv;
	while (env[i] != NULL)
	{
		temp = ft_split(env[i], '=');
		if (!ft_strcmp(temp[0], "HOME"))
			g_global.home = ft_strdup(temp[1]);
		ft_lstadd_back(&env_list,
			ft_envlstnew(ft_strdup(temp[0]), ft_strdup(temp[1])));
		i++;
		ft_free_array(temp);
	}
	init_readline(&env_list);
	ft_e_lstclear(&env_list);
	free(g_global.home);
}
