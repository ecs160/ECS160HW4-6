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

int findTweeter(struct tweet *tweeterArrayTemp, char *name ){
	
	for (int i = 0; i < sizeof(tweeterArrayTemp); i++){
		// printf("string: %s name: %s ", tweeterArrayTemp[i].tweeter, name);
		if (!strcmp(tweeterArrayTemp[i].tweeter, name))
			return 0;
	}
	return -1;
}


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
 
 	tweet tweeterArray[MAX_LINES_PER_FILE];
	// tweet* tweetArray =(void*) malloc( sizeof(struct tweet));
	memset(tweeterArray, 0, MAX_LINES_PER_FILE * sizeof(struct tweet)); 
	

	while (fgets(line, MAX_CHAR_PER_LINE, fd)) {
		char* token;
		char* tmp = strdup(line);
		int num_cols = 0;
		while ((token = strsep(&tmp, ",")) != NULL) {
			if (num_lines == 0) {
				if (!strcmp(token, "name") || !strcmp(token, "\"name\""))
					tweeter_col = num_cols;
			} else if (num_cols == tweeter_col){
				 if (num_lines < 1 ){
				perror("invalid number of lines in file\n");
				return -1;
				}
				tweeterArray[num_lines].tweeter = token;
				tweeterArray[num_lines].count = 1;
          
      }
			num_cols++;
		}
		num_lines++;
	}

	if (num_lines <= 0 || num_lines >= MAX_LINES_PER_FILE) {
		perror("invalid number of lines in file\n");
		return -1;
	}

//find the count of all the tweeters
	for (int i = 1; i< num_lines; i++){
		for(int j = 1; j < num_lines ; j++){
			if (!strcmp(tweeterArray[j].tweeter , tweeterArray[i].tweeter) && i != j){
				tweeterArray[i].count++;
			}		
		}
	}

//array that will hold the final tweeters and their counts
	tweet finalArray[10];
	for(int j = 0; j < 10; j++){
		finalArray[j].tweeter = "";
		finalArray[j].count = 0;
	}

//iterates through all names and counts to findthe top 10 tweeters
	for (int i = 1; i < num_lines; i++){
		for(int j = 0; j < 10; j++){
			if (strcmp(finalArray[j].tweeter,tweeterArray[i].tweeter) && tweeterArray[i].count >finalArray[j].count && findTweeter(finalArray, tweeterArray[i].tweeter)){
				finalArray[j].tweeter = tweeterArray[i].tweeter;
				finalArray[j].count= tweeterArray[i].count;
			}		
		}
	}

//display the top 10 tweeters and their counts
	for (int i = 0; i < 10; i++){
		printf("tweeter: %s, count: %d\n", finalArray[i].tweeter,finalArray[i].count);
	}



	if (fclose(fd) != 0) {
		fprintf(stderr, "file close failure: %s\n", strerror(errno));
		return -1;
	}

	return 0;
}