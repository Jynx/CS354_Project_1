//Steven Volocyk, Lecture 001
/* This program reads a file of binary numbers and 
prints out a human-readable format*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

int
main(int argc, char *argv[]) {
    
    int readFile;//for input file
    
    if (argc != 2) {
        fprintf(stderr, "Usage: intcat <file>\n");
        exit(1);
    }  

    if ((readFile = open(argv[1], O_RDONLY)) < 0) {
        /*file didn't open */
        printf("Could not open file %s\n", argv[1]);
        exit(1);
    }
    int i = 0;
    while ((read(readFile, &i, sizeof(i)) > 0)) {
        printf("%d\n", i);
    }

    close(readFile);

    return 0;
}    
