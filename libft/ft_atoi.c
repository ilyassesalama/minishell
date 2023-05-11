/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:08:56 by isalama           #+#    #+#             */
/*   Updated: 2023/05/07 16:20:35 by isalama          ###   ########.fr       */
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

static int	is_space(char str)
{
	return (str == 32 || (str >= 9 && str <= 13));
}

static int	has_sign(char str)
{
	return (str == '-' || str == '+');
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while (is_space(str[i]))
		i++;
	if (has_sign(str[i]))
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	return (process_result((char *)str, sign, i));
}
