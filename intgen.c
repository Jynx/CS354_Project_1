#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

long int random(void);
void srandom(unsigned int seed);

int
main(int argc, char *argv[])
{
    int count;   /* number of integers to write out */
    int seed;    /* integer seed for the random value generator */
    int fd;      /* file descriptor */
    int i;       /* temporary - loop induction variable */
    int value;   /* random integer generated */

    if (argc != 4) {
	fprintf(stderr, "usage: intgen <file> <count> <seed>\n");
	exit(1);
    }

    count = atoi(argv[2]); // atoi() converts C string to an integer
    if  ( count % 2 != 0 ){
        /* only working with even numbers of integers generated */
	fprintf(stderr, "usage: intgen <file> <count> <seed>\n   <count> must be a positive, even integer value\n");
	exit(1);
    }
    seed = atoi(argv[3]);
    (void) srandom(seed);

    if ( (fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU)) < 0 ) {
        /* file did not open */
        printf("Could not open file %s\n", argv[1]);
	exit(1);
    }

    for (i = 0; i < count; i++) {
	value = (random() % 50000) - 25000;
        if (write(fd, &value, sizeof(int))  != sizeof(int) ) {
            printf("bad write to file %s\n", argv[1]);
	    exit(1);
        }
    }

    close(fd);

    return 0;
}

