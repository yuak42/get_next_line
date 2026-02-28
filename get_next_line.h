/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuak <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 14:31:11 by yuak              #+#    #+#             */
/*   Updated: 2025/08/25 14:33:03 by yuak             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*find_new_line(int fd, char *line, char *buffer);
char	*catch_line(char *buffer);
char	*connect_buffer(char *line, char *buffer);
void	shift_buffer(char *buffer);
int		is_new_line(char *line);
char	*create_and_reset(size_t size);
size_t	ft_strlen(char *str);

#endif
