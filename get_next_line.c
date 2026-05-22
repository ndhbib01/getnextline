/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahabib <<marvin@42.fr>>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 19:13:13 by hahabib           #+#    #+#             */
/*   Updated: 2026/05/22 15:40:47 by hahabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	stash = read_and_append(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = update_stash(stash);
	return (line);
}

char	*read_and_append(int fd, char *stash)
{
	char	*buffer;
	int		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_stash_buffer(stash, buffer));
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		stash = join_and_free(stash, buffer);
		if (!stash)
			return (free_stash_buffer(NULL, buffer));
	}
	free(buffer);
	return (stash);
}

char	*join_and_free(char *stash, char *buffer)
{
	char	*temp;

	temp = stash;
	stash = ft_strjoin(stash, buffer);
	free(temp);
	return (stash);
}

char	*extract_line( char *stash)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	if (!stash || !stash[0])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
	{
		i++;
	}
	if (stash[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*update_stash(char *stash)
{
	int		i;
	int		j;
	char	*new_stash;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free_stash_buffer(stash, NULL));
	i++;
	new_stash = malloc(sizeof(char) * (ft_strlen(stash + i) + 1));
	if (!new_stash)
		return (free_stash_buffer(stash, NULL));
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}
