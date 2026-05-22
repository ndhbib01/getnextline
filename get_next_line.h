/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hahabib <<marvin@42.fr>>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 16:19:50 by hahabib           #+#    #+#             */
/*   Updated: 2026/05/22 15:23:55 by hahabib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <stdlib.h>

/*--------------------GNL Functions------------------*/
char	*get_next_line(int fd);
char	*read_and_append(int fd, char *stash);
char	*free_stash_buffer(char *stash, char *buffer);
char	*join_and_free(char *stash, char *buffer);
char	*extract_line(char *stash);
char	*update_stash(char *stash);

/*-------------------String Utilities----------------*/
char	*ft_strchr(char *stash, int letter);
char	*ft_strjoin(char *stash, char *buffer);
size_t	ft_strlen(char *string);
char	*free_stash(char *stash);

#endif
