/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_creator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 20:05:24 by isalama           #+#    #+#             */
/*   Updated: 2023/05/19 20:35:10 by isalama          ###   ########.fr       */
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

t_token		*tokens_creation(char *input)
{
	int 	i;
	int 	start;
	
	t_token *tokens = NULL;
	
	i = 0;
	while(input[i])
	{
		if (input[i] && input[i] == ' ')
		{
			ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_strdup(" "), SPACE));
			while (input[i] == ' ')
				i++;
		}
		else if (input[i] && input[i] == '\'')
		{
			i++;
			start = i;
			while (input[i] && input[i] != '\'')
				i++;
			ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_substr(input, start, i - start), SINGLE_QUOTE));
			i++;
		}
		else if (input[i] && input[i] == '\"')
		{
			i++;
			start = i;
			while (input[i] && input[i] != '\"')
				i++;
			ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_substr(input, start, i - start), DOUBLE_QUOTE));
			i++;
		}
		else if (input[i] && input[i] == '|')
		{
			ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_strdup("|"), PIPE));
			i++;
		}
		else if ((input[i] && input[i + 1]) && input[i] == '>' && input[i + 1] == '>')
		{
			ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_strdup(">>"), APPEND));
			i += 2;
		}
		else if ((input[i] && input[i + 1]) && input[i] == '<' && input[i + 1] == '<')
		{
			ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_strdup("<<"), HEREDOC));
			i += 2;
		}
		else if (input[i] && input[i] == '>')
		{
			ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_strdup(">"), REDIR));
			i++;
		}
		else if (input[i] && input[i] == '<')
		{
			ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_strdup("<"), DREDIR));
			i++;
		}
		else 
		{
			start = i;
			while(input[i] && input[i] != ' ' && input[i] != '|' && input[i] != '>' && input[i] != '<')
				i++;
			ft_t_lstadd_back(&tokens, ft_t_lstnew(ft_substr(input, start, i - start), WORD));
		}

		// pwd
		// ls
	}
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