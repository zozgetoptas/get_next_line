#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char *line;
    int fd = open("regular.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("dosya yok");
        return (-1);
    }
    while((line = get_next_line(fd)))
    {
        printf("%s\n",line);
        free (line);
    }
    close(fd);
    return (0);
}