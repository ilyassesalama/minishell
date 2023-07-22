/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_filler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 05:36:28 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/22 02:39:05 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	**args_filler(char **args, char *token)
{
	char	**tmp2d;
	int		i;

	i = 0;
	if (!args)
	{
		tmp2d = malloc(sizeof(char *) * 2);
		if (!tmp2d)
			return (NULL);
		tmp2d[0] = ft_strdup(token);
		return (tmp2d[1] = NULL, tmp2d);
	}
	while (args[i])
		i++;
	tmp2d = malloc(sizeof(char *) * (i + 2));
	if (!tmp2d)
		return (NULL);
	i = 0;
	while (args[i])
	{
		tmp2d[i] = ft_strdup(args[i]);
		i++;
	}
	return (tmp2d[i] = ft_strdup(token), tmp2d[i + 1] = NULL,
		ft_free_array(args), tmp2d);
}

int	command_filler_2(t_token **tokens, char **command, char ***args)
{
	if ((*tokens) && (*tokens)-> type == WORD)
	{
		*args = ft_split((*tokens)-> content, ' ');
		*command = ft_strdup((*args)[0]);
		if (!*command)
		{
			free(*command);
			*command = ft_strdup("");
		}
		return ((*tokens) = (*tokens)-> next, 0);
	}
	if ((*tokens) && ((*tokens)-> type == DOUBLE_QUOTE
			|| (*tokens)-> type == SINGLE_QUOTE))
		return (*command = ft_strdup((*tokens)-> content),
			*args = args_filler((*args), (*tokens)-> content),
			(*tokens) = (*tokens)-> next, 0);
	if (!(*tokens))
	{
		*command = ft_strdup("");
		*args = malloc(sizeof(char *) * 1);
		if (!*args)
			return (0);
		(*args)[0] = NULL;
	}
	return (0);
}

t_command	*command_filler(t_token *tokens, t_command *com, int in, int out)
{
	t_command	*tmp;
	char		*command;
	char		**args;

	args = NULL;
	command = NULL;
	if (tokens -> type == NONUSABLE || tokens -> type == SPACER)
	{
		while (tokens && (tokens -> type == NONUSABLE
				|| tokens -> type == SPACER))
			tokens = tokens -> next;
	}
	command_filler_2(&tokens, &command, &args);
	while (tokens && tokens -> type != PIPE)
	{
		if (tokens -> type == SPACER || tokens -> type == NONUSABLE)
			tokens = tokens -> next;
		else
		{
			args = args_filler(args, tokens -> content);
			tokens = tokens -> next;
		}
	}
	tmp = ft_c_lstnew(command, args, in, out);
	return (ft_c_lstadd_back(&com, tmp), com);
}
