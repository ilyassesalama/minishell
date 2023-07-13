/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 02:41:10 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/13 01:07:05 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
 t_token	*ft_t_SPACERs_deleter(t_token *tokens)
 {
	if (tokens && tokens -> type == SPACER)
	{
		t_token *tmp = tokens -> next;
		free(tokens);
		tokens = tmp;
	}
	if (tokens && ft_t_lstlast(tokens, 1) -> type == SPACER)
	{
		t_token *tmp = ft_t_lstlast(tokens, 1);
		free(tmp);
		tmp = NULL;
		tmp = ft_t_lstlast(tokens, 0);
		tmp -> next = NULL;
	}
	return (tokens);
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

t_token *ft_t_lstlast(t_token *lst, int type)
{
	if (!lst)
		return (NULL);
	if (type == 1)
	{
		while (lst -> next)
			lst = lst -> next;
	}
	else
	{
		while (lst -> next -> next)
			lst = lst -> next;
	}
	return (lst);
}

void	ft_t_delone(t_token *token)
{
	t_token *tmp;

	tmp = NULL;
	if (!token)
		return ;
	if (token -> next)
		tmp = token -> next;
	free(token);
	token = tmp;
}
