/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 22:30:34 by isalama           #+#    #+#             */
/*   Updated: 2023/07/28 10:58:34 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*p;

	p = malloc(count * size);
	if (!p)
		return (NULL);
	ft_bzero (p, count * size);
	return (p);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i + 1] && s[i] == (char) c)
			return ((char *) &s[i + 1]);
		i++;
	}
	if (s[i] == (char) c)
		return ((char *) &s[i]);
	return (NULL);
}

char	*ft_strrchr(char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char) c)
		{
			return ((char *) &s[i]);
		}
		i--;
	}
	return (NULL);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
