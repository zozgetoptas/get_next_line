# get_next_line

A function that reads and returns one line at a time from a file descriptor, handling memory efficiently with a static buffer.

## Overview

`get_next_line` is a function that reads a line from a file descriptor and returns it. This project demonstrates advanced understanding of file I/O, memory management, and static variables in C.

The function reads from a file descriptor one line at a time, where a line ends with a newline character (`\n`) or when the end of file is reached.

## Features

- Reads one complete line from a file descriptor
- Handles multiple file descriptors simultaneously
- Efficient memory management with configurable buffer size
- Returns NULL at end of file or on error
- Works with any valid file descriptor (files, stdin, pipes, etc.)
- Bonus version supports reading from multiple file descriptors

## Function Signature

```c
char	*get_next_line(int fd);
```

### Parameters
- `fd`: File descriptor to read from

### Return Value
- A pointer to the next line (including the newline character if present)
- `NULL` if end of file is reached or an error occurs
- Memory is allocated for each line and must be freed by the caller

## Project Structure

- **get_next_line.c**: Main function implementation
- **get_next_line.h**: Function declaration and macro definition
- **get_next_line_utils.c**: Helper functions (string manipulation)
- **get_next_line_bonus.c**: Bonus version (multiple file descriptors)
- **get_next_line_utils_bonus.c**: Helper functions for bonus version

### Key Macros

- `BUFFER_SIZE`: Defines the read buffer size (default: 256 bytes)
  - Can be changed at compile time: `gcc -D BUFFER_SIZE=4096 ...`

## Usage Example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    if (fd == -1)
        return (1);
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    
    close(fd);
    return (0);
}
```

## Compilation

With default buffer size (256 bytes):
```bash
gcc -c get_next_line.c get_next_line_utils.c
gcc -c get_next_line_bonus.c get_next_line_utils_bonus.c  # For bonus
```

With custom buffer size:
```bash
gcc -D BUFFER_SIZE=4096 -c get_next_line.c get_next_line_utils.c
```

## Implementation Details

### Core Concepts

1. **Static Buffer**: Uses a static variable to maintain remainder of data between calls
2. **Line Extraction**: Separates the current complete line from remaining data
3. **Memory Management**: Allocates memory for each line returned
4. **Multiple File Descriptors**: Bonus version handles multiple FDs using an array of static buffers

### Algorithm Flow

1. Read data from file descriptor into buffer
2. Check if newline exists in remainder + new data
3. Extract and return the complete line
4. Store remaining data for the next call
5. Repeat until EOF or error

## Important Notes

- **Memory Responsibility**: The caller must `free()` each returned line
- **Buffer Size Trade-off**: Larger buffer = fewer system calls but more memory per read
- **Error Handling**: Returns `NULL` on malloc failure or read error
- **EOF Behavior**: After returning the last line (without newline), subsequent calls return `NULL`
- **File Descriptor Validity**: Ensure the file descriptor remains valid between calls

## Bonus Features

The bonus version (`get_next_line_bonus.c`) supports:
- Reading from different file descriptors in any order
- Each file descriptor maintains its own buffer independently
- Seamless switching between multiple files

## Common Issues & Solutions

**Issue**: Same line returned multiple times
- **Solution**: Ensure you're freeing each line and advancing the file descriptor correctly

**Issue**: Memory leaks
- **Solution**: Free every line returned by the function

**Issue**: Incomplete lines returned
- **Solution**: Check if BUFFER_SIZE is appropriate for your use case

