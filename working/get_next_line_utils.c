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
	if (!str)
		return (0);
	while (str[len])
	{
		len++;
	}
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	if ((char)c == '\0')
	{
		return ((char *)s);
	}
	return (NULL);
}

char	*ft_strdup(const char *str)
{
	size_t	str_len;
	char	*duplicate_str;
	size_t	i;

	if (!str)
		return (NULL);
	str_len = ft_strlen(str);
	duplicate_str = (char *)malloc((str_len + 1) * sizeof(char));
	if (duplicate_str == NULL)
		return (NULL);
	i = 0;
	while (i < str_len)
	{
		duplicate_str[i] = str[i];
		i++;
	}
	duplicate_str[str_len] = '\0';
	return (duplicate_str);
}

char	*ft_strjoin(char *s1, const char *s2)
{
	char	*junction;
	size_t	lens1;
	size_t	lens2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	junction = malloc(lens1 + lens2 + 1);
	if (!junction)
		return (NULL);
	ft_strlcpy(junction, s1, lens1 + 1);
	ft_strlcpy(junction + lens1, s2, lens2 + 1);
	return (junction);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_src;

	i = 0;
	len_src = 0;
	while (src[len_src] != '\0')
	{
		len_src++;
	}
	if (size > 0)
	{
		while (src[i] != '\0' && i < (size - 1))
		{
		dst[i] = src[i];
		i++;
		}
		dst[i] = '\0';
	}
	return (len_src);
}
