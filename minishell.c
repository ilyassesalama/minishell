/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:10:08 by isalama           #+#    #+#             */
/*   Updated: 2023/05/11 20:55:57 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
	char *receiver;
	while (1)
	{
		receiver = readline("minishell: ");
		if(receiver == NULL)
			break;
		printf("%s\n", receiver);
	}
}
