#include <stdio.h>
#include <fcntl.h>
#include "get_next_line_bonus.h"

int main()
{
    char *line;
    int fd1 = open("multiplefd.txt", O_RDONLY);
    int fd2 = open("multiplefd2.txt", O_RDONLY);
    int fd3 = open("multiplefd3.txt", O_RDONLY);
     if (fd1 == -1 || fd2 == -1 || fd3 == -1)
    {
        perror("Bir veya daha fazla dosya acilirken hata olustu");
        if (fd1 != -1) close(fd1);
        if (fd2 != -1) close(fd2);
        if (fd3 != -1) close(fd3);
        return 1;
    }

int fd1_active = 1;
int fd2_active = 1;
int fd3_active = 1;

while (fd1_active || fd2_active || fd3_active)
{
    if (fd1_active) {
        line = get_next_line(fd1);
        if (line) {
            printf("FD1: %s\n", line);
            free(line);
        } else {
            printf("FD1: (EOF veya Hata)\n");
            close(fd1);
            fd1_active = 0;
        }
    }
    if (fd2_active) {
        line = get_next_line(fd2);
        if (line) {
            printf("FD2: %s\n", line);
            free(line);
        } else {
            printf("FD2: (EOF veya Hata)\n");
            close(fd2);
            fd2_active = 0;
        }
    }
    if (fd3_active) {
        line = get_next_line(fd3);
        if (line) {
            printf("FD3: %s\n", line);
            free(line);
        } else {
            printf("FD3: (EOF veya Hata)\n");
            close(fd3);
            fd3_active = 0;
        }
    }

    if (!fd1_active && !fd2_active && !fd3_active)
        break;
}
return 0;
}