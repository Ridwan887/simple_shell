#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define MAX_LINE_SIZE 1024

static char input_buffer[MAX_LINE_SIZE];
static size_t buffer_position = 0;
static size_t buffer_size = 0;

ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream) {
    ssize_t bytesRead = 0;
    ssize_t totalBytesRead = 0;

    if (lineptr == NULL || n == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (buffer_size == 0) {
        // Read a batch of characters into the buffer
        buffer_size = read(fileno(stream), input_buffer, sizeof(input_buffer));
        if (buffer_size == (size_t)-1) {

            return -1;
        }
        buffer_position = 0;
    }

    while (buffer_position < buffer_size) {
        char current_char = input_buffer[buffer_position++];
        (*n)++; // Increment the length of the line

        if (current_char == '\n') {
            // Found a newline character, terminate the line
            (*lineptr)[bytesRead++] = '\0';
            return totalBytesRead + bytesRead - 1; // Exclude the null terminator
        }

        // Check if we need to reallocate the line buffer
        if ((size_t)bytesRead >= *n) {
            *n *= 2; // Double the buffer size
            *lineptr = realloc(*lineptr, *n);
            if (*lineptr == NULL) {
                return -1;
            }
        }

        (*lineptr)[bytesRead++] = current_char;
        totalBytesRead++;
    }

    // If we reach here, we've read all available data without finding a newline character
    buffer_size = 0; // Reset buffer since it's fully consumed
    return -1; // Line is longer than the buffer size, so we return an error
}

int main_(void) {
    char *line = NULL;
    size_t len = 0;

    while (1) {
        ssize_t bytesRead = custom_getline(&line, &len, stdin);

        if (bytesRead == -1) {
            // Error or line too long
            printf("Error reading line.\n");
            break;
        } else if (bytesRead == 0) {
            // End of file (Ctrl+D)
            printf("\n");
            break;
        } else {
            // Successfully read a line
            printf("Read %zd bytes: %s\n", bytesRead, line);
        }
    }

    free(line);
    return 0;
}
