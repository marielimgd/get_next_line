/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marieli <marieli@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:28:25 by mmariano          #+#    #+#             */
/*   Updated: 2025/01/07 09:10:33 by marieli          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_and_store(int fd, char *buffer)
{
	char	*read_buffer;
	int		bytes_read;

	read_buffer = malloc(BUFFER_SIZE + 1);
	if (!read_buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(buffer, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(read_buffer);
			free(buffer);
			return (NULL);
		}
		read_buffer[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, read_buffer);
	}
	free(read_buffer);
	return (buffer);
}

char	*extract_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer || !buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*extract_remaining(char *buffer)
{
	int		i;
	int		j;
	char	*remaining_content;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	remaining_content = malloc(ft_strlen(buffer) - i);
	if (!remaining_content)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		remaining_content[j++] = buffer[i++];
	remaining_content[j] = '\0';
	free(buffer);
	return (remaining_content);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_and_store(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = extract_remaining(buffer);
	return (line);
}
