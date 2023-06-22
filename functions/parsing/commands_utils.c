/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 04:53:48 by tajjid            #+#    #+#             */
/*   Updated: 2023/06/16 02:05:08 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		fd_opener(char *file, int mode)
{
	int		fd = 0;

	if (mode == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (mode == 2)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (mode == 3)
		fd = open(file, O_RDONLY);
	return (fd);
}

t_command	*ft_c_lstnew(char *command , char **args, int input, int output)
{
	t_command	*new;

	new = (t_command *)malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->command = command;
	new->args = args;
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

void	non_use_remover(t_token *tokens)
{
	t_token *tmp;
	t_token *tmp2;

	tmp = tokens;
	while (tmp)
	{
		if (tmp -> next && tmp -> next -> type == NONUSABLE)
		{
			tmp2 = tmp -> next;
			tmp -> next = tmp -> next -> next;
			free(tmp2);
			if (tmp -> next && tmp -> next -> type == SPACE)
			{
				tmp2 = tmp -> next;
				tmp -> next = tmp -> next -> next;
				free(tmp2);
			}
		}
		else
			tmp = tmp -> next;
	}
}
