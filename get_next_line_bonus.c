#include <unistd.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"

static char *extract_current_line(char *remainder)
{
    char    *current_line;
    char    *found_new_line;
    size_t  current_line_len;

    if (!remainder || remainder[0] == '\0')
        return (NULL);
    found_new_line = ft_strchr(remainder, '\n');
    if (found_new_line)
        current_line_len = found_new_line - remainder + 1;
    else
        current_line_len = ft_strlen(remainder);
    current_line = malloc(current_line_len + 1);
    if (!current_line)
        return (NULL);
    ft_strlcpy(current_line, remainder, current_line_len + 1);
    return (current_line);
}

static char *update_remainder(char *remainder)
{
    char    *new_remainder;
    char    *found_new_line;

    found_new_line = ft_strchr(remainder, '\n');
    if (!found_new_line)
    {
        free(remainder);
        return (NULL);
    }
    new_remainder = ft_strdup(found_new_line + 1);
    free(remainder);
    return (new_remainder);
}

static char *read_and_join(int fd, char *remainder)
{
    char    *buffer;
    ssize_t read_byte;
    char    *temp;

    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
    {
        free(remainder);
        return (NULL);
    }
    read_byte = 1;
    while (read_byte > 0 && (!remainder || !ft_strchr(remainder, '\n')))
    {
        read_byte = read(fd, buffer, BUFFER_SIZE);
        if (read_byte == -1)
        {
            free(buffer);
            free(remainder);
            return (NULL);
        }
        buffer[read_byte] = '\0';
        temp = remainder;
        remainder = ft_strjoin(temp, buffer);
        free(temp);
        if (!remainder)
        {
            free(buffer);
            return (NULL);
        }
    }
    free(buffer);
    return (remainder);
}

static char *start_remainder(char *remainder)
{
    if (!remainder)
    {
        remainder = ft_strdup("");
        if (!remainder)
            return (NULL);
    }
    return (remainder);
}

char    *get_next_line(int fd)
{
    static char *remainder[MAX_FD];
    char        *current_line;

    if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
        return (NULL);
    remainder[fd] = start_remainder(remainder[fd]);
    if (!remainder[fd])
        return (NULL);
    remainder[fd] = read_and_join(fd, remainder[fd]);
    if (!remainder[fd])
    {
        remainder[fd] = NULL;
        return (NULL);
    }
    current_line = extract_current_line(remainder[fd]);
    if (!current_line)
    {
        free(remainder[fd]);
        remainder[fd] = NULL;
        return (NULL);
    }
    remainder[fd] = update_remainder(remainder[fd]);
    return (current_line);
}