/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_creator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 04:43:28 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/20 22:53:59 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	files_checker(t_token **tokens, t_cmdtls *t)
{
	if ((*tokens)-> type == APPEND || (*tokens)-> type == OUT_REDIR)
		files_opener((tokens), (*tokens)-> type, &t->output);
	else if ((*tokens)-> type == IN_REDIR)
		dredir_opener((tokens), (*tokens)-> type, &t->input);
	(*tokens) = (*tokens)-> next;
}

void	here_doc_present(t_token **tokens, t_env *env)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		if (tmp -> type == HEREDOC)
			heredoc_handler(&tmp, 0, 1, env);
		tmp = tmp -> next;
	}
}

void	pipe_commander(t_cmdtls *t, t_token **tokens)
{
	if (t->no_file == 1)
		t->input = -1;
	if (t->no_file == 2)
		t->output = -1;
	t->commands = command_filler(t->tmp_tokens2, t->commands,
			t->input, t->output);
	t->input = 0;
	t->output = 1;
	t->flag = 1;
	t->no_file = 0;
	if ((*tokens)-> type == SPACER)
		(*tokens) = (*tokens)-> next;
}

t_command	*command_creator(t_token *tokens, t_env *env)
{
	t_cmdtls	t;

	ft_memset(&t, 0, sizeof(t_cmdtls));
	t.tmp_tokens2 = tokens;
	t.output = 1;
	here_doc_present(&tokens, env);
	while (tokens)
	{
		if (t.input == -1)
			t.no_file = 1;
		if (t.output == -1)
			t.no_file = 2;
		if (t.flag == 1)
		{
			t.tmp_tokens2 = tokens;
			t.flag = 0;
		}
		if (tokens -> type == PIPE)
			pipe_commander(&t, &tokens);
		files_checker(&tokens, &t);
	}
	return (command_filler(t.tmp_tokens2, t.commands, t.input, t.output));
}
