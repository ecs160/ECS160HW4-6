#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FILE_LENGTH 20000

typedef struct tweeter {
	char* tweeter;
	int count;
} tweet;

int main(int argc, char** argv)
{
    /* 
     * 1. read csv line by line 
     * 2. error check the max length of each line
     * 3. error check the max number of lines in file 
     * 

     
     * A valid input csv file has columns separated with “,”’s, but you cannot 
     * assume the location of the tweeter column will be fixed to a particular
     * location (like 8 for instance).
     

     
     * A valid csv file will have a header, and the tweeter column will be called
     * “name”, and the items may or may not be surrounded by quotes (“/”).
     

    
    * a valid file will not have additional commas inside the tweet. However, 
    * your program should not crash on any input, even invalid ones
    */
    printf("Starting HW maxTweeter\n");
    if (argc != 2 || argv[0] == NULL || argv[1] == NULL) {
      perror("invalid input\n");
      return -1;
    }

    FILE* fd = fopen(argv[1], "r");
    if (fd == NULL) {
      fprintf(stderr, "%s: %s\n", argv[1], strerror(errno));
      return -1;
    }
    printf("Input file: %s\n", argv[1]);

    char line[MAX_LINE_LENGTH];
    int lines = 0;
    // float lenTotal = 0;

    while (fgets(line, MAX_LINE_LENGTH, fd))
      {
          char* tmp = strdup(line);
          printf("line %d contains: %s", lines,tmp);
          lines++;

      }

    if (fclose(fd) != 0) {
      fprintf(stderr, "file close failure: %s\n", strerror(errno));
      return -1;
    }

    return 0;
}