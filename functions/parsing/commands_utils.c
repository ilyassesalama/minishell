/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 04:53:48 by tajjid            #+#    #+#             */
/*   Updated: 2023/05/21 00:14:14 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		fd_opener(char *file, int mode)
{
	int		fd;

	if (mode == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (mode == 2)
		fd = open(file, O_WRONLY | O_CREAT , 0777);
	else
		fd = open(file, O_RDONLY);
	return (fd);
}

t_command	*ft_c_lstnew(char *command, int input, int output)
{
	t_command	*new;

	new = (t_command *)malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->command = command;
	new->input = input;
	new->output = output;
	new->next = NULL;
	return (new);
}

void	ft_c_lstadd_back(t_command **list, t_command *new)
{
	t_command	*temp;

	if (!*list)
	{
		*list = new;
		return ;
	}
	temp = *list;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

void	ft_c_lstclear(t_command **list)
{
	t_command	*temp;

	if (!*list)
		return ;
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->command);
		free(*list);
		*list = temp;
	}
}
