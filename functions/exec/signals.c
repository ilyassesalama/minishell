/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:47:03 by isalama           #+#    #+#             */
/*   Updated: 2023/07/13 17:49:06 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	d_sig_handler(int sig_num)
{
	(void)sig_num;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	slash_sig_handler(int sig_num)
{
	(void)sig_num;
	return ;
}

void    signals_handler(void)
{
	signal(SIGINT, d_sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
