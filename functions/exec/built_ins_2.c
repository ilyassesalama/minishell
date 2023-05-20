/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 19:37:18 by isalama           #+#    #+#             */
/*   Updated: 2023/05/20 03:04:31 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(void)
{
	exit(0);
}

void	ft_env(t_env *env)
{
	t_env	*envirement;

	envirement = env;
	while (envirement)
	{
		ft_putstr_fd(envirement->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(envirement->value, 1);
		ft_putstr_fd("\n", 1);
		envirement = envirement->next;
	}
}