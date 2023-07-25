/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 12:04:45 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/25 10:17:42 by tajjid           ###   ########.fr       */
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
	if (commands == NULL)
		return ;
	ft_t_lstclear(&tokens);
	tokens_execution(commands, env);
	ft_c_lstclear(&commands);
}

void	init_readline(t_env **env_list)
{
	int		i;
	char	*receiver;
	char	*command;

	i = 0;
	command = "\001\033[32m\002 minishell:\001\033[0m\002 ";
	while (true)
	{
		signals_handler();
		g_global.heredoc_eof = 0;
		receiver = readline(command);
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
	char	**sp;
	t_env	*en_v;

	en_v = NULL;
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
		sp = ft_split(env[i], '=');
		if (ft_strcmp(sp[0], "HOME") == 0)
			g_global.home = ft_strdup(sp[1]);
		ft_lstadd_back(&en_v, ft_envlstnew(ft_strdup(sp[0]), ft_strdup(sp[1])));
		i++;
		ft_free_array(sp);
	}
	init_readline(&en_v);
	ft_e_lstclear(&en_v);
	free(g_global.home);
}
