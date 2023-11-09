/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsinagl <vsinagl@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 18:05:29 by vsinagl           #+#    #+#             */
/*   Updated: 2023/11/09 18:09:34 by vsinagl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	char	*res;

	res = (char *)s;
	if (c > 127)
		return (res);
	while (*res != '\0')
	{
		if (*res == c)
			return (res);
		res++;
	}
	if (*res == c)
		return (res);
	return (NULL);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*p_dest;
	unsigned char		*p_src;
	size_t				i;

	p_dest = (unsigned char *)dest;
	p_src = (unsigned char *)src;
	i = 0;
	if (!dest && !src)
		return (dest);
	if (src < dest)
	{
		while (n--)
			p_dest[n] = p_src[n];
	}
	else
	{
		while (n--)
		{
			p_dest[i] = p_src[i];
			i++;
		}
	}
	return (dest);
}

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*res;

	i = 0;
	res = (char *)s;
	if (c > 125)
		return (res);
	while (res[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (res[i] == c)
			return (res + i);
		i--;
	}
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*sdup;
	size_t	n;

	n = 0;
	sdup = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (sdup == NULL)
		return (NULL);
	while (s[n] != '\0')
	{
		sdup[n] = s[n];
		n++;
	}
	sdup[n] = '\0';
	return (sdup);
}
