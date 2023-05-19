/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 02:41:10 by tajjid            #+#    #+#             */
/*   Updated: 2023/05/19 02:54:24 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token		*ft_t_lstnew(char *content, int type)
{
	t_token *new;
	
	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new -> content = content;
	new -> type = type;
	new -> next = NULL;
	return (new);
}

void	ft_t_lstadd_back(t_token **alst, t_token *new)
{
	t_token	*last;
	
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

void	ft_t_delone(t_token **token)
{
	if (!token)
		return ;
	free(*token);
	*token = NULL;
}

void	ft_t_lstclear(t_token **lst)
{
	t_token	*tmp;
	
	if (!lst)
		return ;
	while (*lst)
	{
		tmp = (*lst) -> next;
		free(*lst);
		*lst = tmp;
	}
}

t_token		*ft_t_blstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next -> next)
		lst = lst -> next;
	return (lst);
}

t_token *ft_t_lstlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}
