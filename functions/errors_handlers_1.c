/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handlers_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 23:11:35 by isalama           #+#    #+#             */
/*   Updated: 2023/05/11 23:16:04 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_quotes(char *input)
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
				out_error(ERROR_MSG_QUOTE);
		}
		if (input[i] == '\"')
		{
			i++;
			while (input[i] && input[i] != '\"')
				i++;
			if (input[i] == '\"')
				i++;
			else 
				out_error(ERROR_MSG_QUOTE);
		}
		if (input[i] != '\'' && input[i] != '\"')
			i++;
	}
}