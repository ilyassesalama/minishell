/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 02:41:10 by tajjid            #+#    #+#             */
/*   Updated: 2023/05/20 04:28:54 by tajjid           ###   ########.fr       */
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
 t_token	*ft_t_spaces_deleter(t_token *tokens)
 {
	if (tokens && tokens -> type == SPACE)
	{
		t_token *tmp = tokens->next;
		free(tokens);
		tokens = tmp;
	}
	if (tokens && ft_t_lstlast(tokens) -> type == SPACE)
	{
		t_token *tmp = ft_t_lstlast(tokens);
		free(tmp);
		tmp = NULL;
		tmp = ft_t_blstlast(tokens);
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
