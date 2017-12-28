/**
 * Programming Problem 2.26
 */


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char in[64], out[64];
    FILE *infile, *outfile;
    int c;

    printf("This program copies the contents of one file to destination file.\n");

    printf("Enter name of file to be copied: ");
    scanf("%63s", in);

    printf("Enter name of destination file: ");
    scanf("%63s", out);

    if ((infile = fopen(in, "r")) == NULL) {
        printf("Can't open %s for reading. Aborted.\n", in);
        exit(EXIT_FAILURE);
    }

    if ((outfile = fopen(out, "w")) == NULL) {
        printf("Can't open %s for writing. Aborted.\n", out);
        exit(EXIT_FAILURE);
    }

    while ((c = getc(infile)) != EOF)
        putc(c, outfile);

    fclose(infile);
    fclose(outfile);

    printf("File has been copied.\n");
    
    return EXIT_SUCCESS;
}
