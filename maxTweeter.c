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

void sort(tweet array[], int n)
{
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0 ; j < n - i - 1; j++) {
			if (array[j].count < array[j + 1].count) {
				tweet swap_var = array[j];
				array[j] = array[j + 1];
				array[j + 1] = swap_var;
			}
		}
	}
}

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

	char line[MAX_CHAR_PER_LINE];
	int unique_tweet_count = 0, num_lines = 0, tweeter_col = -1;
	tweet tweets[MAX_LINES_PER_FILE];

	while (fgets(line, MAX_CHAR_PER_LINE, fd)) {
		char* token;
		char* tmp = strdup(line);
		int num_cols = 0;
		while ((token = strsep(&tmp, ",")) != NULL) {
			if (num_lines == 0) {
				if (!strcmp(token, "name") || !strcmp(token, "\"name\""))
					tweeter_col = num_cols;
			} else if (num_cols == tweeter_col) {
				int found_index = -1;
				for (int i = 0; i < unique_tweet_count; i ++) {
					if (!strcmp(tweets[i].tweeter, token)) {
						found_index = i;
						break;
					}
				}
				if (found_index == -1) {
					tweets[unique_tweet_count].tweeter = token;
					tweets[unique_tweet_count].count = 1;
					unique_tweet_count++;
				} else
					tweets[found_index].count++;
			}
			num_cols++;
		}
		num_lines++;
	}

	sort(tweets, unique_tweet_count);
	for (int i = 0; i < unique_tweet_count; i++)
		printf("%s:\t%d\n", tweets[i].tweeter, tweets[i].count);

	if (fclose(fd) != 0) {
		fprintf(stderr, "file close failure: %s\n", strerror(errno));
		return -1;
	}

	return 0;
}