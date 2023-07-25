/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 00:37:19 by isalama           #+#    #+#             */
/*   Updated: 2023/07/25 17:22:38 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

bool	is_exportable(char *identifier)
{
	int	index;

	index = 0;
	if (!(is_alpha(identifier[index]) || identifier[index] == '_')
		|| identifier[index] == '\0')
		return (false);
	index++;
	while (identifier[index] && identifier[index] != '+'
		&& identifier[index] != '=')
	{
		if (!(is_alpha(identifier[index]) || is_digit(identifier[index])
				|| identifier[index] == '_'))
			return (false);
		index++;
	}
	if (identifier[index] == '+' && (!identifier[index + 1]
			|| (identifier[index + 1] && identifier[index + 1] != '=')))
		return (false);
	if (identifier[index] && identifier[index] != '='
		&& identifier[index] != '+')
		return (false);
	return (true);
}

void	export_to_env(t_env **env, char *identifier)
{
	int		index;

	index = 0;
	while (identifier[index] && identifier[index] != '='
		&& identifier[index] != '+')
		index++;
	if (identifier[index] == '+')
		export_append(env, index, identifier);
	else if (identifier[index] == '=')
		export_new(env, index, identifier, true);
	else
		export_new(env, index, identifier, false);
}

void	lets_export(t_env **env, char **args)
{
	int	index;

	index = true;
	while (args[index])
	{
		if (is_exportable(args[index]))
			export_to_env(env, args[index]);
		else
			ft_putstr_fd(ERROR_MSG_IDENTIFIER, 2);
		index++;
	}
}
