/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:29:20 by jaemyu            #+#    #+#             */
/*   Updated: 2025/08/30 15:59:28 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	new_line_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*mine_line(int fd, char *buf, char *storage)
{
	int	read_size;

	if (storage && new_line_check(storage) != -1)
		return (storage);
	read_size = read(fd, buf, BUFFER_SIZE);
	if (read_size < 0)
		return (NULL);
	if (read_size >= 0)
		buf[read_size] = '\0';
	while (read_size > 0)
	{
		storage = gnl_strjoin(storage, buf);
		if (!storage)
			return (NULL);
		if (new_line_check(storage) != -1)
			return (storage);
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size >= 0)
			buf[read_size] = '\0';
	}
	return (storage);
}

char	*residue(char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!line || *line == '\0')
		return (NULL);
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (NULL);
	tmp = gnl_strdup(line + i + 1);
	if (tmp == NULL)
		return (NULL);
	if (tmp[0] == '\0')
	{
		free(tmp);
		tmp = NULL;
		return (NULL);
	}
	line[i + 1] = '\0';
	return (tmp);
}

void	buf_free(char **storage, char **buf)
{
	if (storage)
		free(*storage);
	*storage = NULL;
	free(*buf);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	char		*result;
	static char	*storage;

	if (fd < 0 || BUFFER_SIZE < 1)
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	buf[BUFFER_SIZE] = 0;
	line = mine_line(fd, buf, storage);
	if (!line)
		return (buf_free(&storage, &buf), NULL);
	storage = residue(line);
	result = gnl_strdup(line);
	free(line);
	line = NULL;
	free(buf);
	return (result);
}
