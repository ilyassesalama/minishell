/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 04:53:48 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/17 05:07:34 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

// int	fd_opener(char *file, int mode)
// {
// 	int	fd;

// 	fd = 0;
// 	if (mode == 1)
// 		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 	else if (mode == 2)
// 		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
// 	else if (mode == 3)
// 		fd = open(file, O_RDONLY);
// 	return (fd);
// }

t_command	*ft_c_lstnew(char *command, char **args, int input, int output)
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

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
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
		if ((*list)->args)
			ft_free_array((*list)->args);
		free(*list);
		*list = temp;
	}
}
