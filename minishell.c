/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:10:08 by isalama           #+#    #+#             */
/*   Updated: 2023/05/11 23:12:48 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct t_input_holder *input_holder;

void scan_input(char *input){	
	input_holder = ft_lstnew(input);
	
	handle_quotes(input);
	
}

int main()
{
	char *receiver;
	char *input_command = "\033[1;31m➜ \033[1;32mminishell: \033[0m";
		
	while (true)
	{
		receiver = readline(input_command);
		if(receiver == NULL)
			break;
		if (ft_strlen(receiver) > 0) add_history(receiver);
		
		scan_input(receiver);
	}
}
