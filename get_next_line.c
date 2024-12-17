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

char	*get_next_line(int fd)
{
	int	readbytes;
	char *cupbuffer;

	cupbuffer = ft_calloc(3 + 1, sizeof(char));
	if (!cupbuffer)
		return (NULL);
	readbytes = read(fd, cupbuffer, 3);
	return (cupbuffer);
	if (readbytes <= 0)
		return (NULL);
	return (cupbuffer);
}

#include "get_next_line.h" 

char	*read_file_with_malloc(int fd, char *store_until_n)
{
	char	*buffer;          
	char	*old_adress;      
	int		store_read_bytes; 

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char)); 
	if (!buffer) 
		return (NULL);
	while (!ft_strchr(store_until_n, '\n')) 
	{
		store_read_bytes = read(fd, buffer, BUFFER_SIZE); 
		if (store_read_bytes == -1) 
		{
			return (free(buffer), free(store_until_n), 
				store_until_n = NULL, buffer = NULL, NULL);
		}
		buffer[store_read_bytes] = '\0'; 
		old_adress = store_until_n; 
		store_until_n = ft_strjoin(store_until_n, buffer); 
		free(old_adress); 
		old_adress = NULL; 
		if (store_read_bytes < BUFFER_SIZE) 
			break ;
	}
	return (free(buffer), buffer = NULL, store_until_n); 
}

void	extract_after_n(char *store_until_n, char *remainder_line)
{
	int	i;

	i = 0;
	while (store_until_n[i] != '\n' && store_until_n[i] != '\0') 
		i++;
	if (store_until_n[i] == '\n') 
	{
		ft_strlcpy(remainder_line, &store_until_n[i + 1], BUFFER_SIZE); 
		store_until_n[i + 1] = '\0'; 
	}
}

char	*get_next_line(int fd)
{
	char		*store_until_n;             
	static char	remainder_line[BUFFER_SIZE]; 

	if (fd < 0 || BUFFER_SIZE <= 0) 
		return (NULL);
	store_until_n = ft_strdup(remainder_line); 
	if (!store_until_n) 
		return (NULL);
	remainder_line[0] = '\0'; 

	store_until_n = read_file_with_malloc(fd, store_until_n); 
	if (!store_until_n || store_until_n[0] == '\0') 
	{
		free(store_until_n); 
		store_until_n = NULL; 
		return (NULL);
	}
	if (ft_strchr(store_until_n, '\n')) 
		extract_after_n(store_until_n, remainder_line); 
	return (store_until_n); 
}