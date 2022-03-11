// #include <stdio.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <stdlib.h>
// #include "get_next_line_utils.c"
#include "get_next_line.h"

char    *check_remainder(char *remainder, char **line)
{
    char    *p_n;

    p_n = NULL;
    if (remainder)
    {
        p_n = ft_strchr(remainder, '\n');
        if (p_n)
        {
            *p_n = '\0';
            *line = ft_strdup(remainder);
            ft_strcpy(remainder, ++p_n);
        }
        else
        {
            *line = ft_strdup(remainder);
            //ft_strclr(remainder);
        }
    }
    else
        *line = "\0";
    return (p_n);
}

char    *get_next_line(int fd)
{
    char            *buff;
    int             bytes_was_read;
    char            *line;
    char            *p_n;
    static  char    *remainder;

    line = "\0";
    buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buff)
        return (NULL);
    p_n = check_remainder(remainder, &line);
    bytes_was_read = read(fd, buff, BUFFER_SIZE);
    while (!p_n && bytes_was_read)
    {
        buff[bytes_was_read] = '\0';
        p_n = ft_strchr(buff, '\n');
        if (p_n)
        {
            *p_n = '\0';
            remainder = ft_strdup(++p_n);
        }
        line = ft_strjoin(line, buff);
        if (!p_n)
            bytes_was_read = read(fd, buff, BUFFER_SIZE);
    }
    return (line);
}

// int main()
// {
//     int     fd;
//     char    *line;

//     fd = open("test.txt", O_RDONLY);
//     line = get_next_line(fd);
//     printf("%s\n", line);
//     line = get_next_line(fd);
//     printf("%s\n", line);
//     line = get_next_line(fd);
//     printf("%s\n", line);
// }