/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmariano <mmariano@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:28:25 by mmariano          #+#    #+#             */
/*   Updated: 2024/12/17 12:48:30 by mmariano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *read_file(int  fd, char *store_until_n)
{
    char *buffer;
    char  *prev_store;
    int  store_read_char;

    buffer = malloc((BUFFER_SIZE +1)); 
    if (!buffer)
        return(NULL); 
    while (!ft_strchr(store_until_n, '\n')) 
    {
        store_read_char = read(fd, buffer, BUFFER_SIZE); 
        if (store_read_char == -1) 
            return (free(buffer), free(store_until_n), buffer = NULL, store_until_n = NULL, NULL);
        buffer[store_read_char] = '\0'; 
        prev_store = store_until_n; 
        store_until_n = ft_strjoin(store_until_n, buffer); 
        free(prev_store); 
        prev_store = NULL; 
        if (store_read_char < BUFFER_SIZE) 
            break;
    }
    free(buffer);
    buffer = NULL;
    return (store_until_n); 
}

void    extract_after_n(char *store_until_n, char *leftovers)
{
    while (*store_until_n != '\n' && *store_until_n != '\0')
        store_until_n++;
    if (*store_until_n == '\n')
    {
        store_until_n++;
        ft_strlcpy(leftovers,store_until_n, BUFFER_SIZE);
        store_until_n[-1] = '\0';
    }
}

char    *get_next_line(int  fd)
{
    char    *store_until_n; 
    static char leftovers[BUFFER_SIZE]; 

    
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    store_until_n = ft_strdup(leftovers); 
    if (!store_until_n) 
        return (NULL);
    leftovers[0] = '\0'; 

    store_until_n = read_file(fd, store_until_n); 

    
    if (!store_until_n || store_until_n[0] == '\0')
    {
        free(store_until_n);
        store_until_n = NULL;
        return(NULL);
    }
    if (ft_strchr(store_until_n, '\n'))
        extract_after_n(store_until_n, leftovers);
    return(store_until_n);
}
