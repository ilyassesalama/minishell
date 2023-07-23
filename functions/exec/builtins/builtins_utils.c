/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 03:12:07 by isalama           #+#    #+#             */
/*   Updated: 2023/07/23 11:56:59 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

bool	is_builtin(t_command *commands)
{
	char	*builtins[8];
	int		i;

	builtins[0] = "cd";
	builtins[1] = "pwd";
	builtins[2] = "exit";
	builtins[3] = "echo";
	builtins[4] = "env";
	builtins[5] = "export";
	builtins[6] = "unset";
	builtins[7] = NULL;
	i = 0;
	while (builtins[i])
	{
		if (commands->command && ft_strcmp(commands->command, builtins[i]) == 0)
			return (true);
		i++;
	}
	return (false);
}
