#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

char *get_next_line(int fd)
{
    char    *buf;

    buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buf)
        return (NULL);
    read(fd, buf, BUFFER_SIZE);
    return (buf);
}

int main()
{
    int fd;

    fd = open("test.txt", O_RDONLY);
    char *str = get_next_line(fd);
    printf("%s\n", str);
}