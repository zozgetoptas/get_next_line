#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"
int main()
{
    int fd = open("gnl.txt", O_RDWR | O_CREAT, 0644);
    char *line = "";
    if (fd == -1)
    {
        perror ("acilamadi");
        return (-1);
    }
    while ((line = get_next_line(fd)))
    {
        printf("%s",line);
        free(line);
    }
    close(fd);
    return (0);
}