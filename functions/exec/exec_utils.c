/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 23:35:53 by isalama           #+#    #+#             */
/*   Updated: 2023/05/20 00:18:35 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_command		*command_lstnew(char *command, char **args, int input, int output)
{
	t_command *new;
	
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