#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

typedef struct tweeter {
	char* tweeter;
	int count;
} tweet;

int main(int argc, char** argv)
{
	if (argc != 2 || argv[0] == NULL || argv[1] == NULL) {
		perror("invalid input\n");
		return -1;
	}

	FILE* fd = fopen(argv[1], "r");
	if (fd == NULL) {
		fprintf(stderr, "%s: %s\n", argv[1], strerror(errno));
		return -1;
	}

	if (fclose(fd) != 0) {
		fprintf(stderr, "file close failure: %s\n", strerror(errno));
		return -1;
	}

	return 0;
}
