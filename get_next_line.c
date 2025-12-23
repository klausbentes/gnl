/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:52:03 by kbentes-          #+#    #+#             */
/*   Updated: 2025/12/23 19:25:06 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_has_new_line(char *string)
{
	int	i;

	if (!string)
		return (0);
	i = 0;
	while (string[i] != '\0' && string[i] != '\n')
		i++;
	if (string[i] == '\n')
		return (1);
	return (0);
}

static char	*copy_until_new_line(char *line, const char *buf)
{
	size_t	len_line;
	size_t	len_buf;
	size_t	i;
	char	*new_string;

	if (!line || !buf)
		return (NULL);
	len_line = ft_strlen(line);
	len_buf = 0;
	while (buf[len_buf] && buf[len_buf] != '\n')
		len_buf++;
	new_string = ft_calloc(len_line + len_buf + 2);
	i = 0;
	while (line[i] != '\0')
		new_string[i] = line[i++];
	i = 0;
	while (buf[i] && buf[i] != '\n')
		new_string[len_line + i] = buf[i++];
	new_string[len_line + i] = '\n';
    free(line);
	return (new_string);
}

static char *ft_read_line(int fd, char *stash)
{
    char    *buf;
    char    *line;
    ssize_t bytes_read;

    buf = ft_calloc(BUFFER_SIZE + 1, 1);
    // Se já havia algo em stash (o resto de uma chamada anterior):
    line = NULL;
    if (stash != NULL)
    {
        *buf = stash;
        free(stash);
        bytes_read = ft_strlen(buf);
    }
    else // primeira chamada
        bytes_read = read(fd, buf, (size_t) BUFFER_SIZE);
    // Dentro de um while, verificar se há \n no meu buf
    while (ft_has_new_line(buf) == 0 && bytes_read > 0) // leu algo e não tem new_line
    {
        line = copy_until_new_line(line, buf); // se line for NULL, line vai apontar pra uma string que é igual a buf
        bytes_read = read(fd, buf, BUFFER_SIZE);
    }
    // Adiciona tudo que foi lido até \n na line
    line = copy_until_new_line(line, buf);
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

    return (ft_read_line(fd, stash));
}
