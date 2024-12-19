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

size_t ft_strlen(char *s)
{
    size_t i = 0;

    if (!s)
        return (0);
    while (s[i] != '\0')
        i++;
    return (i);
}

char *ft_strchr(char *s, int c)
{
    int i = 0;

    if (!s)
        return (NULL);
    if (c == '\0')
        return ((char *)&s[ft_strlen(s)]);
    while (s[i] != '\0')
    {
        if (s[i] == (char)c)
            return ((char *)&s[i]);
        i++;
    }
    return (NULL);
}

char *ft_strjoin(char *s1, char *s2)
{
    size_t len1, len2, i, j;
    char *result;

    if (!s1)
    {
        s1 = (char *)malloc(1 * sizeof(char));
        if (!s1)
            return (NULL);
        s1[0] = '\0';
    }
    len1 = ft_strlen(s1);
    len2 = ft_strlen(s2);
    result = malloc(sizeof(char) * (len1 + len2 + 1));
    if (!result)
        return (NULL);
    for (i = 0; i < len1; i++)
        result[i] = s1[i];
    for (j = 0; j < len2; j++)
        result[i++] = s2[j];
    result[len1 + len2] = '\0';
    free(s1);
    return (result);
}
