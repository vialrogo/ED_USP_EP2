/*
 * main.c            File with the functions for read/write the input/output
 *                   files, ---- 
 *                   and main method with the calls to these functions.
 * Create by:        Victor Alberto Romero Gonzalez
 *
 */

#include <stdio.h>

/* Global variables*/
int numeroVertices;

void readInputFile(char* inputFileName)
{
    /* File reader */
    FILE* fileIn;
    int from, to, cost;
    
    fileIn = fopen (inputFileName, "r");
    fscanf (fileIn, "%d", &from);
    fscanf (fileIn, "%d", &to);
    fscanf (fileIn, "%d", &cost);

    while(!feof (fileIn)) /* While o file still has numbers */
    {
        printf ("%d %d %d\n", from, to, cost);
        fscanf (fileIn, "%d", &from);
        fscanf (fileIn, "%d", &to);
        fscanf (fileIn, "%d", &cost);
    }

    /* Close file, and zering pointer*/
    fclose(fileIn);
    fileIn=0;
}

int main(int argc, char *argv[])
{
    char* inputFileName;

    /* Correct number of parameters? */
    if(argc<2)
    {
        printf("Incorrect number of parameters!\n");
        return 1;
    }
    inputFileName  = argv[1];

    readInputFile(inputFileName);

    return 0;
}
