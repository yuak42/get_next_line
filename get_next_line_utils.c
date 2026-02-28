/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuak <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:31:17 by yuak              #+#    #+#             */
/*   Updated: 2025/08/25 14:31:19 by yuak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	shift_buffer(char *buffer)
{
	int	i;
	int	j;

	if (*buffer == '\0' || buffer == NULL)
		return ;
	i = 0;
	j = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
	{
		i++;
		while (buffer[i] != '\0')
		{
			buffer[j] = buffer[i];
			i++;
			j++;
		}
	}
	while (buffer[j] != '\0')
	{
		buffer[j] = '\0';
		j++;
	}
}

int	is_new_line(char *line)
{
	int	i;

	if (line == NULL)
		return (0);
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		return (1);
	return (0);
}

char	*create_and_reset(size_t size)
{
	char	*temp;
	size_t	i;

	temp = (char *) malloc(size * sizeof(char));
	if (!temp)
		return (NULL);
	i = 0;
	while (i < size)
	{
		temp[i] = '\0';
		i++;
	}
	return (temp);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}
