#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include <stdbool.h>

#define MAX_CHAR_PER_LINE 1024
#define MAX_LINES_PER_FILE 20000

typedef struct tweet {
	char* tweeter;
	int count;
} tweet;


int main(int argc, char** argv)
{
	/*
	 * A valid input csv file has columns separated with “,”’s, but you cannot
	 * assume the location of the tweeter column will be fixed to a particular
	 * location (like 8 for instance).

	 * A valid csv file will have a header, and the tweeter column will be called
	 * “name”, and the items may or may not be surrounded by quotes (“/”).

	 * a valid file will not have additional commas inside the tweet. However,
	 * your program should not crash on any input, even invalid ones
	 *
	 */

	if (argc != 2 || argv[0] == NULL || argv[1] == NULL) {
		perror("invalid input\n");
		return -1;
	}

	FILE* fd = fopen(argv[1], "r");
	if (fd == NULL) {
		fprintf(stderr, "%s: %s\n", argv[1], strerror(errno));
		return -1;
	}

	char line[MAX_CHAR_PER_LINE];
	int num_lines = 0, tweeter_col = -1;

	/*
		You may also assume that the maximum line length of any valid csv file will not be longer than 1024 characters, the length of the file will not exceed 20,000 lines.
	*/

	while (fgets(line, MAX_CHAR_PER_LINE, fd)) {
		char* token;
		char* tmp = strdup(line);
		int num_cols = 0;
		while ((token = strsep(&tmp, ",")) != NULL) {
			if (num_lines == 0) {
				if (!strcmp(token, "name") || !strcmp(token, "\"name\""))
					tweeter_col = num_cols;
			} else if (num_cols == tweeter_col)
				printf("tweeter: %s\n", token);
			num_cols++;
		}
		num_lines++;
	}


	if (num_lines <= 0 || num_lines >= MAX_LINES_PER_FILE) {
		perror("invalid number of lines in file\n");
		return -1;
	}

	if (fclose(fd) != 0) {
		fprintf(stderr, "file close failure: %s\n", strerror(errno));
		return -1;
	}

	return 0;
}