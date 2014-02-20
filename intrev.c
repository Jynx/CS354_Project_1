//Steven Volocyk, Lecture 001
/* This program reads a file of binary numbers and 
prints out a human-readable format. However, it reverses
the order of the binary numbers in the file. */


#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int
main(int argc, char *argv[]) {

	int numInts; // Var for filesize
    FILE *inputFile, *outputFile; //I/O pointers
	int i, ret; // loop/return control
	int *ptrArray; //pointer to an array
    char *yar = argv[1]; //pointer to first arg

	if (argc != 3) {
		fprintf(stderr, "Usage: intrev <inputfile> <outputfile> ");
		exit(1);
	}
    inputFile = fopen(argv[1], "r");
    struct stat fileStat;
    stat(yar, &fileStat);
    // assume file has a series of 4 byte integers, so divide by 4*
    numInts = (fileStat.st_size/sizeof(int));

    ptrArray = (int*)malloc(numInts * sizeof(int));
    if (!ptrArray) {
    	printf("Could not allocate %d bytes for Integer array." 
    		"The system is out of memory. \n", numInts);
    	exit(1);
    }
    /* read contents of inputFile, which is assumed to have
    items of size 4, place in array*/
    fread(ptrArray,sizeof(int), numInts, inputFile);
	
    ret = 0;
    outputFile = fopen(argv[2], "w");
    if (outputFile) {
    	// write contents of array to outputFile backwards 
    	for (i = numInts - 1; i >= 0; i--) {
    		fwrite(&ptrArray[i],sizeof(int), 1, outputFile);
    	}
    }		
    else {
    	printf("could not open file %s\n", argv[2]);
    	ret = 1;
    }
    fclose(inputFile);
    fclose(outputFile);
    free(ptrArray);
    return ret;
}    