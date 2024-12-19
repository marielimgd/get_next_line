/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:28:19 by mmariano          #+#    #+#             */
/*   Updated: 2024/12/17 12:49:06 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strdup(const char *src)
{
	char	*dest;
	size_t	index;
	size_t	len;

	len = (ft_strlen(src) + 1);
	dest = (char *)malloc(len);
	if (dest == NULL)
		return (NULL);
	index = 0;
	while (src[index] != '\0')
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
		{
			return ((char *)str);
		}
		str++;
	}
	if ((char)c == '\0')
	{
		return ((char *)str);
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	size_t	index;
	size_t	index_str;
	char	*new_str;

	index = 0;
	index_str = 0;
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_str = (char *)malloc(total_len);
	if (!new_str)
		return (NULL);
	while (s1[index])
		new_str[index_str++] = s1[index++];
	index = 0;
	while (s2[index])
		new_str[index_str++] = s2[index++];
	new_str[index_str] = '\0';
	return (new_str);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t destsize)
{
	size_t	src_len;
	size_t	index;

	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	if (destsize > 0)
	{
		index = 0;
		while (index < (destsize - 1) && src[index] != '\0')
		{
			dest[index] = src[index];
			index++;
		}
		dest[index] = '\0';
	}
	return (src_len);
}
