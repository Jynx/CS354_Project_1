#include <stdio.h>
#include <assert.h>
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
    if (argc != 4) {
	fprintf(stderr, "usage: strgen <file> <count> <seed>\n");
	exit(1);
    }
    char *infile = argv[1];
    int count    = atoi(argv[2]); // need to call atoi() to CONVERT string to an integer
    int seed     = atoi(argv[3]);
    assert(count > 0);

    (void) srandom(seed);

    FILE *fp = fopen(infile, "w");
    assert(fp != NULL);

    int i;
    for (i = 0; i < count; i++) {
	int value = (random() % 50000) - 25000;
	fprintf(fp, "%d;", value);
    }

    fclose(fp);

    return 0;
}

