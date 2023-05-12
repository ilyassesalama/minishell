/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tajjid <tajjid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 23:01:54 by tajjid            #+#    #+#             */
/*   Updated: 2023/05/12 17:53:55 by tajjid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_len(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;

	i = 0;
	while (s[start + i] != '\0' && i < len)
		i++;
	return (i);
}

char	*ft_substr(char const *s, int start, size_t len)
{
	int		i;
	int		k;
	char	*ptr;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	i = 0;
	k = ft_len(s, start, len);
	ptr = ft_calloc (k + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	while (k)
	{
		ptr[i] = s[start + i];
		i++;
		k--;
	}
	return (ptr);
}
