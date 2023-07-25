/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isalama <isalama@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:50:03 by tajjid            #+#    #+#             */
/*   Updated: 2023/07/25 17:16:30 by isalama          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;

	str = b;
	while (len)
	{
		*str = (unsigned char)c;
		str++;
		len--;
	}
	return (b);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	ls1;
	char	*ss1;

	ls1 = ft_strlen (s1);
	if (!s1)
		return (NULL);
	i = 0;
	ss1 = malloc(sizeof(char) * (ls1 + 1));
	if (!ss1)
		return (NULL);
	while (s1[i])
	{
		ss1[i] = s1[i];
		i++;
	}
	ss1[i] = '\0';
	return (ss1);
}

char	*ft_strjoin(char *s1, char *s2, int flag)
{
	char	*ptr;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	ptr = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1 * sizeof(char));
	if (!ptr)
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	if (s1 && flag == 1)
		free(s1);
	if (s2 && flag == 2)
		free(s2);
	return (ptr);
}

bool	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (true);
	return (false);
}

bool	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}
