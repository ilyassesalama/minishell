/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_filler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 05:36:28 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/17 05:13:49 by isalama          ###   ########.fr       */
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
		tmp2d[0] = ft_strdup(token);
		tmp2d[1] = NULL;
		return (tmp2d);
	}
	while (args[i])
		i++;
	tmp2d = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (args[i])
	{
		tmp2d[i] = ft_strdup(args[i]);
		i++;
	}
	tmp2d[i] = ft_strdup(token);
	tmp2d[i + 1] = NULL;
	ft_free_array(args);
	return (tmp2d);
}

void	command_filler_2(t_token **tokens, char **command, char ***args)
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
		(*tokens) = (*tokens)-> next;
	}
	else if ((*tokens) && ((*tokens)-> type == DOUBLE_QUOTE
			|| (*tokens)-> type == SINGLE_QUOTE))
	{
		*command = ft_strdup((*tokens)-> content);
		*args = args_filler((*args), (*tokens)-> content);
		(*tokens) = (*tokens)-> next;
	}
	else if (!(*tokens))
	{
		*command = ft_strdup("");
		*args = malloc(sizeof(char *) * 1);
		(*args)[0] = NULL;
	}
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
