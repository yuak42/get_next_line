/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuak <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:31:05 by yuak              #+#    #+#             */
/*   Updated: 2025/09/03 16:16:50 by yuak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(buffer), buffer = NULL, NULL);
	if (!buffer)
		buffer = create_and_reset(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (is_new_line(buffer))
		return (catch_line(buffer));
	line = create_and_reset(1);
	if (!line)
		return (free(buffer), buffer = NULL, NULL);
	line = connect_buffer(line, buffer);
	if (!line)
		return (free(buffer), buffer = NULL, NULL);
	line = find_new_line(fd, line, buffer);
	if (!line)
		return (free(buffer), buffer = NULL, NULL);
	shift_buffer(buffer);
	if (*buffer == '\0')
		return (free(buffer), buffer = NULL, line);
	return (line);
}

char	*find_new_line(int fd, char *line, char *buffer)
{
	ssize_t	read_bytes;
	char	*temp;

	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(line), NULL);
		buffer[read_bytes] = '\0';
		line = connect_buffer(line, buffer);
		if (!line)
			return (NULL);
		if (is_new_line(line))
			return (temp = line, line = catch_line(line), free(temp), line);
	}
	if (*line == '\0')
		return (free(line), NULL);
	return (line);
}

char	*catch_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	while (buffer[i] != '\n')
		i++;
	line = create_and_reset(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\n';
	shift_buffer(buffer);
	return (line);
}

char	*connect_buffer(char *line, char *buffer)
{
	char	*temp;
	int		i;
	int		j;

	temp = create_and_reset(ft_strlen(line) + ft_strlen(buffer) + 1);
	if (!temp)
		return (free(line), NULL);
	i = 0;
	while (line[i])
	{
		temp[i] = line[i];
		i++;
	}
	free(line);
	j = 0;
	while (buffer[j])
	{
		temp[i] = buffer[j];
		j++;
		i++;
	}
	return (temp);
}
