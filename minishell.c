/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:10:08 by isalama           #+#    #+#             */
/*   Updated: 2023/05/11 19:25:42 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_cum
{
	int		a;
	int		b;
	char	*str;
}				cum;

int main()
{
	ft_putstr_fd("-> minishell: ", 1);
	while (1)
	{
		read(0, 0, 1);
	}
}
albgbz