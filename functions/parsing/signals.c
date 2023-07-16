/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 05:15:27 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/16 05:16:06 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	heredoc_sigint(int sigint)
{
	if (sigint != SIGINT)
		return ;
	if (g_global.heredoc_eof == 1)
	{
		g_global.heredoc_eof = 0;
		return ;
	}
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	g_global.heredoc_eof = 1;
}

void	herdoc_signal(void)
{
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}
