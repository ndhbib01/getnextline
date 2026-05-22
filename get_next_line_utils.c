/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahabib <<marvin@42.fr>>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 16:19:29 by hahabib           #+#    #+#             */
/*   Updated: 2026/05/22 14:57:02 by hahabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*joined_string(char *stash, char *buffer, char *joined);

size_t	ft_strlen(char *string)
{
	size_t	i;

	if (!string)
		return (0);
	i = 0;
	while (string[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *stash, char *buffer)
{
	char	*joined;
	size_t	len1;
	size_t	len2;

	if (!stash)
		len1 = 0;
	else
		len1 = ft_strlen(stash);
	if (!buffer)
		return (NULL);
	else
		len2 = ft_strlen(buffer);
	joined = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!joined)
		return (NULL);
	joined = joined_string(stash, buffer, joined);
	return (joined);
}

static char	*joined_string(char *stash, char *buffer, char *joined)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (stash)
	{
		while (stash[i])
		{
			joined[i] = stash[i];
			i++;
		}
	}
	while (buffer[j])
	{
		joined[i + j] = buffer[j];
		j++;
	}
	joined[i + j] = '\0';
	return (joined);
}

char	*ft_strchr(char *stash, int letter)
{
	if (!stash)
		return (NULL);
	while (*stash)
	{
		if (*stash == (char)letter)
			return ((char *)stash);
		stash++;
	}
	if ((char)letter == '\0')
		return ((char *)stash);
	return (NULL);
}

char	*free_stash_buffer(char *stash, char *buffer)
{
	free(stash);
	free(buffer);
	return (NULL);
}
