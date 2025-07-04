#include <unistd.h>
#include "get_next_line_bonus.h"
#include <stdlib.h>

static char	*extract_current_line(char *remainder)
{
	char	*current_line;
	char	*found_new_line;
	size_t	current_line_len;

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

static char	*update_remainder(char *remainder)
{
	char	*new_remainder;
	char	*found_new_line;

	found_new_line = ft_strchr(remainder, '\n');
	if (!found_new_line)
	{
		free(remainder);
		return (NULL);
	}
	if (*(found_new_line + 1) == '\0')
	{
		new_remainder = ft_strdup("");
	}
	else
	{
		new_remainder = ft_strdup(found_new_line + 1);
	}
	free(remainder);
	return (new_remainder);
}

static char	*join_buffers(char *remainder, char *buffer)
{
	char	*temp;
	char	*new_remainder;

	temp = remainder;
	new_remainder = ft_strjoin(temp, buffer);
	free(temp);
	if (!new_remainder)
		return (NULL);
	return (new_remainder);
}

static char	*read_from_fd(int fd, char *remainder)
{
	char	*buffer;
	ssize_t	read_byte;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(remainder), NULL);
	read_byte = 1;
	while (read_byte > 0 && (!ft_strchr(remainder, '\n')))
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte == -1)
			return (free(buffer), free(remainder), NULL);
		buffer[read_byte] = '\0';
		remainder = join_buffers(remainder, buffer);
		if (!remainder)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder[1024];
	char		*current_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	if (!remainder[fd])
	{
		remainder[fd] = ft_strdup("");
		if (!remainder[fd])
			return (NULL);
	}
	remainder[fd] = read_from_fd(fd, remainder[fd]);
	if (!remainder[fd])
		return (NULL);
	current_line = extract_current_line(remainder[fd]);
	if (!current_line)
		return (free(remainder[fd]), remainder[fd] = NULL, NULL);
	remainder[fd] = update_remainder(remainder[fd]);
	return (current_line);
}
