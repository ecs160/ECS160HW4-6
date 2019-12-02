#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>

#define tw_error(fmt, ...) 		\
	fprintf(stderr, "%s: "fmt"\n", __func__, ##__VA_ARGS__)

#define die(...)				\
do {							\
	tw_error(__VA_ARGS__);		\
	exit(1);					\
} while (0)

#define die_perror(msg)			\
do {							\
	perror(msg);				\
	exit(1);					\
} while (0)

#define MAX_CHAR_PER_LINE 1024
#define MAX_LINES_PER_FILE 20000
#define min(a, b) (a < b ? a : b)

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

void print(tweet tweets[], int n)
{
	for (int i = 0; i < n; i++)
		printf("%s:\t%d\n", tweets[i].tweeter, tweets[i].count);
}

void trim(char *str)
{
	int count = 0;
	for (int i = 0; str[i]; i++)
		if (!isspace(str[i]))
			str[count++] = str[i];
	str[count] = '\0';
}

bool surrounded_by(char* str, char c)
{
	return str[0] == c || str[strlen(str) - 1] == c;
}

bool not_surrounded_by(char* str, char c)
{
	return str[0] != c || str[strlen(str) - 1] != c;
}

bool header_exists(char* headers[], char* str, int n)
{
	for (int i = 0; i < n; i++) {
		if (!strcmp(headers[i], str))
			return true;
	}
	return false;
}

int find_index(tweet tweets[], char* str, int n)
{
	for (int i = 0; i < n; i++) {
		if (!strcmp(tweets[i].tweeter, str))
			return i;
	}
	return -1;
}

FILE* get_fd(int argc, char** argv)
{
	if (argc != 2 || argv[0] == NULL || argv[1] == NULL)
		die("Invalid input format");

	FILE* fd = fopen(argv[1], "r");
	if (fd == NULL)
		die_perror(argv[1]);
	return fd;
}

int main(int argc, char** argv)
{
	FILE* fd = get_fd(argc, argv);
	tweet tweets[MAX_LINES_PER_FILE];
	char* headers[MAX_CHAR_PER_LINE];
	char line[MAX_CHAR_PER_LINE];
	int unique_tw_count = 0, unique_header_count = 0;
	int num_cols =  0, num_headers = 0, num_lines = 0, tweeter_col = -1;
	bool header_quotes = false;

	while (fgets(line, MAX_CHAR_PER_LINE, fd)) {
		char* token;
		char* tmp = strdup(line);
		num_cols = 0;
		num_lines++;
		while ((token = strsep(&tmp, ",")) != NULL) {
			num_cols++;
			if (num_lines == 1 && strlen(token) > 0 && strcmp(token, "\n")) {
				trim(token);
				if (!header_quotes && surrounded_by(token, '"'))
					header_quotes = true;
				if (header_quotes && not_surrounded_by(token, '"'))
					die("Inconsistent header quotes");

				if (header_exists(headers, token, unique_header_count))
					die("Invalid Duplicate Header");
				else
					headers[unique_header_count++] = token;

				if (!strcmp(token, "name") || !strcmp(token, "\"name\""))
					tweeter_col = num_cols;
			} else if (num_lines > 1 && tweeter_col == -1)
				die("Header not found: `name`");
			else if (num_cols == tweeter_col && strlen(token) > 0) {
				int tweet_index = find_index(tweets, token, unique_tw_count);
				if (tweet_index == -1) {
					tweets[unique_tw_count].tweeter = token;
					tweets[unique_tw_count++].count = 1;
				} else
					tweets[tweet_index].count++;
			}
		}
		if (num_lines == 1)
			num_headers = num_cols;
		else if (num_headers != num_cols)
			die("Inconsistent number of columns");
	}

	sort(tweets, unique_tw_count);
	print(tweets, min(unique_tw_count, 10));

	if (fclose(fd) != 0)
		die_perror(argv[1]);

	return 0;
}