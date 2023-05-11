/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:10:08 by isalama           #+#    #+#             */
/*   Updated: 2023/05/11 21:00:51 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	char *receiver;
	char *inpout_command = "\033[1;31m➜ minishell: \033[0m";
	while (true)
	{
		receiver = readline(inpout_command);
		if(receiver == NULL)
			break;
		printf("%s\n", receiver);
	}
}
