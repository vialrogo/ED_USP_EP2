/*
 * main.c            File with the functions for read/write the input/output
 *                   files, -----------------------------------------------
 *                   and main method with the calls to
 *                   these functions.
 * Create by:        Victor Alberto Romero Gonzalez
 *
 */

#include <stdio.h>

/* Global variables*/

void writeOutputFile(char* outputFileName)
{
   /* File writer */
    FILE* fileOut;
    int i,j,routeSize;
    char str[3500]; /* Its more that the maximum poissible with 1000 cities---------------*/ 
    fileOut = fopen(outputFileName, "w");

    if(fileOut==NULL)
    {
        printf("Cannot open the output file!\n");
    }
    else
    {
        sprintf(str,"Cidade %d ",i); /* Put the city id ----------------------*/
        fputs(str,fileOut);
    }
    
    /* Close file, and zering pointer*/
    fclose(fileOut);
    fileOut=0;
}

void readInputFile(char* inputFileName)
{
    /* File reader */
    FILE* fileIn;
    int from = 0;
    int to = 0;
    
    fileIn = fopen (inputFileName, "r");
    fscanf (fileIn, "%d", &from);
    fscanf (fileIn, "%d", &to);

    while(!feof (fileIn)) /* While o file still has numbers */
    {
        fscanf (fileIn, "%d", &from);
        fscanf (fileIn, "%d", &to);
    }

    /* Close file, and zering pointer*/
    fclose(fileIn);
    fileIn=0;
}

int main(int argc, char *argv[])
{
    char* inputFileName;
    char* outputFileName;

    /* Correct number of parameters? */
    if(argc<2)
    {
        printf("Incorrect number of parameters!\n");
        return 1;
    }
    inputFileName  = argv[1];
    outputFileName = argv[2];

    return 0;
}
