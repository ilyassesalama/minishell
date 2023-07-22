/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 23:35:53 by isalama           #+#    #+#             */
/*   Updated: 2023/07/22 01:37:12 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_resources(t_command *commands, int *pipex)
{
	close(pipex[1]);
	close(pipex[0]);
	if (commands->output != 1 && commands->output != -1)
		close(commands->output);
	if (commands->input != 0 && commands->input != -1)
		close(commands->input);
}

bool	is_non_dir(t_command **commands)
{
	if ((*commands)-> input == -1 || (*commands)-> output == -1)
	{
		ft_putstr_fd(ERROR_MSG, 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		(*commands) = (*commands)-> next;
		return (true);
	}
	return (false);
}

t_command	*command_lstnew(char *command, char **args, int input, int output)
{
	t_command	*new;

	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new -> command = command;
	new -> args = args;
	new -> input = input;
	new -> output = output;
	new -> next = NULL;
	return (new);
}

void	command_add_back(t_command **alst, t_command *new)
{
	t_command	*last;

	if (!alst || !new)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	last = *alst;
	while (last -> next)
		last = last -> next;
	last -> next = new;
}

int	command_lst_size(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}
