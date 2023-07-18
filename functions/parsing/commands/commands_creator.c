/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_creator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 04:43:28 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/18 03:20:12 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	files_checker(t_token **tokens, t_cmdtls *t, t_env *env)
{
	if ((*tokens)-> type == HEREDOC)
		t->input = heredoc_handler((tokens), t->input, t->output, env);
	else if ((*tokens)-> type == APPEND || (*tokens)-> type == OUT_REDIR)
		files_opener((tokens), (*tokens)-> type, &t->output);
	else if ((*tokens)-> type == IN_REDIR)
		dredir_opener((tokens), (*tokens)-> type, &t->input);
	(*tokens) = (*tokens)-> next;
}

t_command	*command_creator(t_token *tokens, t_env *env)
{
	t_cmdtls	t;

	ft_memset(&t, 0, sizeof(t_cmdtls));
	t.tmp_tokens2 = tokens;
	t.output = 1;
	while (tokens)
	{
		if (t.flag == 1)
		{
			t.tmp_tokens2 = tokens;
			t.flag = 0;
		}
		if (tokens -> type == PIPE)
		{
			t.commands = command_filler(t.tmp_tokens2,
					t.commands, t.input, t.output);
			t.input = 0;
			t.output = 1;
			t.flag = 1;
			if (tokens -> next -> type == SPACER)
				tokens = tokens -> next;
		}
		files_checker(&tokens, &t, env);
	}
	return (command_filler(t.tmp_tokens2, t.commands, t.input, t.output));
}
