/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 23:22:00 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/13 01:23:10 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*srcc;
	unsigned char	*dstt;

	i = 0;
	srcc = (unsigned char *)src;
	dstt = (unsigned char *)dst;
	if (src == dst)
		return (dst);
	if (src == dst)
		return (dst);
	while (i < n)
	{
		dstt[i] = srcc[i];
		i++;
	}
	return (dst);
}

static int	int_len(int n)
{
	int	i;

	i = 0;
	while (n)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static char	*ft_anything(int n, int len, char *p)
{
	if (n < 0)
	{
		p[0] = '-';
		n = n * -1;
	}
	while (n)
	{
		len--;
		p[len] = (n % 10) + 48;
		n = n / 10;
	}
	return (p);
}

char	*ft_itoa(int n)
{
	int		sgn;
	int		len;
	char	*p;

	len = int_len(n);
	sgn = 0;
	if (n < 0 || n == 0)
		sgn += 1;
	p = (char *)ft_calloc(len + sgn + 1, sizeof(char));
	if (!p)
		return (NULL);
	if (n == 0)
	{
		ft_memcpy(p, "0", len + 1);
		return (p);
	}
	if (sgn == 0)
		ft_anything(n, len, p);
	if (sgn == 1 && (n != -2147483648))
		ft_anything(n, len + 1, p);
	if (n == -2147483648)
		ft_memcpy(p, "-2147483648", len + 2);
	return (p);
}
