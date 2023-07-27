/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 05:15:27 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/27 13:24:54 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	heredoc_sigint(int sigint)
{
	(void)sigint;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	g_global.heredoc_eof = 1;
}

void	herdoc_signal(void)
{
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
}
