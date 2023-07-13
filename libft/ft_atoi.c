/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:08:56 by isalama           #+#    #+#             */
/*   Updated: 2023/07/13 01:08:55 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	process_result(char *str, int sign, int position)
{
	unsigned long	result;

	result = 0;
	while (ft_isdigit(str[position]))
	{
		result *= 10;
		result += (str[position] - '0');
		position++;
	}
	return (result * sign);
}

static int	is_SPACER(char str)
{
	return (str == 32 || (str >= 9 && str <= 13));
}

static int	has_sign(char str)
{
	return (str == '-' || str == '+');
}

int	ft_atoi(char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while (is_SPACER(str[i]))
		i++;
	if (has_sign(str[i]))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	return (process_result((char *)str, sign, i));
}
