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

bool is_empty(const char *s)
{
	while (*s != '\0') {
		if (!isspace((unsigned char)*s))
			return false;
		s++;
	}
	return true;
}

char *trim_quotes(char *str)
{
	char *end;
	// Trim leading space
	if ((unsigned char)*str == '"') str++;

	if (*str == 0) // All spaces?
		return str;

	// Trim trailing space
	end = str + strlen(str) - 1;
	if (end > str && (unsigned char)*end == '"') end--;

	end[1] = '\0';

	return str;
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
	bool quotes[MAX_CHAR_PER_LINE];
	char line[MAX_CHAR_PER_LINE];
	bool nameFound = false;
	int tw_count = 0, unique_header_count = 0;
	int num_cols = 0, num_headers = 0, num_lines = 0, tweeter_col = -1;

	while (fgets(line, MAX_CHAR_PER_LINE, fd)) {
		char* token;
		char* tmp = strdup(line);
		num_cols = 0;
		num_lines++;
		if (is_empty(tmp))
			continue;
		while ((token = strsep(&tmp, ",")) != NULL) {
			num_cols++;
			if (num_lines == 1 && strlen(token) > 0 && !is_empty(token)) {
				if (surrounded_by(token, '"'))
					quotes[num_cols] = true;
				token = trim_quotes(token);

				if (header_exists(headers, token, unique_header_count))
					die("Invalid Duplicate Header");
				else
					headers[unique_header_count++] = token;

				if (!strcmp(token, "name")) {
					nameFound = true;
					tweeter_col = num_cols;
				}
			} else if (num_lines > 1 && tweeter_col == -1)
				die("Header not found: `name`");
			else if (!is_empty(token)) {
				if ((quotes[num_cols] && not_surrounded_by(token, '"'))
				    || (!quotes[num_cols] && surrounded_by(token, '"')))
					die("Inconsistent quotes");
				if (num_cols == tweeter_col) {
					token = trim_quotes(token);
					int tweet_index = find_index(tweets, token, tw_count);
					if (tweet_index == -1) {
						tweets[tw_count].tweeter = token;
						tweets[tw_count++].count = 1;
					} else
						tweets[tweet_index].count++;
				}
			}
		}
		if (num_lines == 1)
			num_headers = num_cols;
		else if (num_headers != num_cols)
			die("Inconsistent number of columns");
	}
	if (!nameFound)
		die("Header not found: `name`");

	sort(tweets, tw_count);
	print(tweets, min(tw_count, 10));

	if (fclose(fd) != 0)
		die_perror(argv[1]);

	return 0;
}