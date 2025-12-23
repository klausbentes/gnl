/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:52:03 by kbentes-          #+#    #+#             */
/*   Updated: 2025/12/23 16:52:05 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_has_new_line(char *string)
{
	int	i;

	if (!string)
		return (NULL);
	i = 0;
	while (string[i] != '\0' && string[i] != '\n')
		i++;
	if (string[i] == '\n')
		return (1);
	return (0);
}

static char *ft_read_line(int fd, char *stash)
{
    char    *buf;
    char        *line;
    ssize_t bytes_read;
    
    // Se já havia algo em stash (o resto de uma chamada anterior):
    if (stash != NULL)
    {
        *buf = stash;
        free(stash);
        bytes_read = ft_strlen(buf);
    }
    else
        bytes_read = read(fd, buf, (size_t) BUFFER_SIZE);
    // Dentro de um while, verificar se há \n no meu buf
    while (ft_has_new_line(buf) == 0 && bytes_read > 0) // leu algo e não tem new_line
    {
        *line = ft_strjoin(line, buf);
        bytes_read = read(fd, buf, BUFFER_SIZE);
    }
    // Se buf tem \n, stash = ft_strchr(buf, '\n')
    if (ft_has_new_line(buf))
        stash = ft_strdup(ft_strchr(buf, '\n') + 1);
    return (line);
}

char *get_next_line(int fd)
{
    static char *stash = NULL;
    ssize_t     bytes_read;

    // Se não houver arquivo válido para ler ou espaço de memória
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    // buf = NULL;

    return (ft_read_line(fd, stash));
}