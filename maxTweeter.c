#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	if (argc != 2 || argv[0] == NULL || argv[1] == NULL) {
		perror("invalid input\n");
		exit(-1);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		perror("file open failure\n");
		exit(errno);
	}

	if (close(fd) == -1) {
		perror("file close failure\n");
		exit(errno);
	}
}
