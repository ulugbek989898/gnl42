/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_v2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uisroilo <uisroilo@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 14:30:05 by uisroilo          #+#    #+#             */
/*   Updated: 2022/03/10 15:23:08 by uisroilo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h> //open
#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}

void	ft_strclr(char *s)
{
	if (s)
		ft_bzero(s, ft_strlen(s));
}

char    *check_remainder(char *remainder, char **line)
{
    char    *p_n;

    p_n = NULL;
    if (remainder)
    {
        if ((p_n = ft_strchr(remainder, '\n')))
        {
            *p_n = '\0';
            *line = ft_strdup(remainder);
            ft_strcpy(remainder, ++p_n);
        }
        else
        {
            *line = ft_strdup(remainder);
            ft_strclr(remainder);
        }
    }
    else
        *line = "\0";
    return (p_n);
}

char *get_next_line(int fd)
{
    static char     *remainder;

    char            *buf;
    char            *line;
    int             bytes_was_read;
    char            *p_n;
    //char            *temp;

    buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buf)
        return (NULL);
    p_n = check_remainder(remainder, &line);
    while (!p_n && (bytes_was_read = read(fd, buf, BUFFER_SIZE)))
    {
        buf[bytes_was_read] = '\0';
        if ((p_n = ft_strchr(buf, '\n'))) //  buf = Salom\nJus1\0; p_n = \nJus1\0
        {
            *p_n = '\0';    // buf = Salom\0Jus1\0; p_n = \0Jus1\0, \n changed \0
            remainder = ft_strdup(++p_n);
        }
        //temp = line;
        line = ft_strjoin(line, buf);
        //free(temp);
    }
    return (line);
}

int main()
{
    int fd;
    char    *line;
    int     i;

    fd = open("test.txt", O_RDONLY);
    i = 4;
    while (0 < i)
    {
        line = get_next_line(fd);
        printf("%s\n", line);
        i--;
    }
}