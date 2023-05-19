/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handlers_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 23:11:35 by isalama           #+#    #+#             */
/*   Updated: 2023/05/19 21:47:41 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	out_error(char *error_message)
{
	ft_putstr_fd(error_message, 2);
}

void	syntax_error(t_token *tokens)
{
	(void)tokens;
}

bool	handle_quotes(char *input)
{
	int i;
	
	i = 0;
	while(input[i])
	{
		if (input[i] == '\'')
		{
			i++;
			while (input[i] && input[i] != '\'')
				i++;
			if (input[i] == '\'')
				i++;
			else
				return(out_error(ERROR_MSG_QUOTE), false);
		}
		if (input[i] == '\"')
		{
			i++;
			while (input[i] && input[i] != '\"')
				i++;
			if (input[i] == '\"')
				i++;
			else 
				return(out_error(ERROR_MSG_QUOTE), false);
		}
		if (input[i] != '\'' && input[i] != '\"')
			i++;
	}
	return true;
}