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

typedef struct tweeter {
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

    printf("Input file: %s\n", argv[1]);
    char line[MAX_CHAR_PER_LINE];
    int numberOfLines = 0;  
    // char ch; 

    // /* 
    //  * 1. read csv line by line 
    //  * 2. error check the max length of each line (max 1024)
    //  * 3. error check the max number of lines in file (max 20000)
    //  */ 

    numberOfLines = 0;
    while (fgets(line, MAX_CHAR_PER_LINE, fd))
      {
          char* tmp = strdup(line);
          numberOfLines++;
          printf("line %d contains %s", numberOfLines,tmp);
          if (numberOfLines == 1 && getc(fd) == EOF)
            numberOfLines = 0;
      }
      printf("numberofLines: %d\n", numberOfLines);

    if (numberOfLines <= 0 || numberOfLines >= MAX_LINES_PER_FILE) {
      perror("invalid number of lines in file\n");
      return -1;
    }

    if (fclose(fd) != 0) {
      fprintf(stderr, "file close failure: %s\n", strerror(errno));
      return -1;
    }

    return 0;
}