#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

#define	MAXLINE		1024
#define	TAILLEN		10


int main(int argc, char * argv[])
{
	char ** tail_buffer = NULL;
	int MyGetLine(int, char *, int);
	int fd = -1;
	char * buffer = NULL;
	int next_tail_buffer_to_fill = 0;

	int retval = 1;
	if (argc != 2) {
		printf("First command line argument must be a file name.\n");
		goto bottom;
	}

	if ((fd = open(argv[1], O_RDONLY)) < 0) {
		perror("File failed to open");
		goto bottom;
	}

	if ((buffer = (char *) malloc(MAXLINE)) == NULL) {
		printf("Allocating line buffer failed.\n");
		goto bottom;
	}

	if ((tail_buffer = (char **) malloc(TAILLEN * sizeof(char *))) == NULL) {
		printf("Allocating tail buffer pointer array failed.\n");
		goto bottom;
	}

	memset(tail_buffer, 0, sizeof(char *) * TAILLEN);
	int wrapped_around = 0;

	while (MyGetLine(fd, buffer, MAXLINE)) {
		// printf("%s", buffer);
		int line_length = strlen(buffer);
		if (tail_buffer[next_tail_buffer_to_fill])
			free(tail_buffer[next_tail_buffer_to_fill]);
		if ((tail_buffer[next_tail_buffer_to_fill] = (char *) malloc(line_length + 1)) == NULL) {
			printf("Allocating a new line in the tail buffer failed.\n");
			goto bottom;
		}
		memcpy(tail_buffer[next_tail_buffer_to_fill], buffer, line_length + 1);
		next_tail_buffer_to_fill = (next_tail_buffer_to_fill + 1) % TAILLEN;
		if (!next_tail_buffer_to_fill)
			wrapped_around = 1;
	}

	if (!wrapped_around) {
		for (int i = 0; i < next_tail_buffer_to_fill; i++)
			printf("%s", tail_buffer[i]);
	}
	else {
		int i = next_tail_buffer_to_fill;
		do {
			printf("%s", tail_buffer[i]);
			i = (i + 1) % TAILLEN;
		} while (i != next_tail_buffer_to_fill);
	}
	retval = 0;

bottom:
	
	if (tail_buffer != NULL) {
		for (int i = 0; i < TAILLEN; i++) {
			if (tail_buffer[i] != NULL)
				free(tail_buffer[i]);
		}
		free(tail_buffer);
	}

	if (buffer != NULL)
		free(buffer);

	if (fd >= 0)
		close(fd);

	return retval;
}

int MyGetLine(int fd, char * buffer, int buffer_length)
{
	int retval = 0;
	int bytes_read = 0;

	memset(buffer, 0, buffer_length);
	for (int i = 0; i < buffer_length - 1; i++) {
		bytes_read = read(fd, buffer + i, 1);
		if (bytes_read == 0)
			break;
		retval = 1;
		if (*(buffer + i) == '\n')
			break;
	}
	return retval;
}

