/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:30:34 by isalama           #+#    #+#             */
/*   Updated: 2023/05/11 22:31:38 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back(t_input_holder **alst, t_input_holder *new)
{
	t_input_holder	*last;

	if (!alst || !new)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	last = *alst;
	while (last->next)
		last = last->next;
	last->next = new;
}

t_input_holder	*ft_lstnew(char *input_command)
{
	t_input_holder	*new;

	new = (t_input_holder *)malloc(sizeof(t_input_holder));
	if (!new)
		return (NULL);
	new->input_command = input_command;
	new->next = NULL;
	return (new);
}

void	ft_lstclear(t_input_holder **lst)
{
	t_input_holder	*tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
}