/*
 * main.c            File with the functions for read the input files, the sort
 *                   method, auxiliar functions and main method with the calls 
 *                   to these functions.
 * Create by:        Victor Alberto Romero Gonzalez 
 *
 */

#include <stdio.h>

/* Structs definitions*/
struct _Edge
{
   int origNode;
   int destNode;
   int costEdge;
};
typedef struct _Edge Edge;

/* Global variables*/
int i,j;
int numVertex, numNodes;
Edge arrayEdges[10000]; /* Maximun number of edges */
Edge tempArray [10000]; /* Maximun number of edges */
int groupNodes[100];    /* Maximun number of cities */

/* Method definitions */
void initialize()
{
    numVertex=0;
    numNodes=0;

    for(i=0;i<100;i++)
        groupNodes[i]=0;
}

void readInputFile(char* inputFileName)
{
    FILE* fileIn;
    int from, to, cost;
    
    fileIn = fopen (inputFileName, "r");
    
    /* Try to read the next vals*/
    fscanf (fileIn, "%d", &from);
    fscanf (fileIn, "%d", &to);
    fscanf (fileIn, "%d", &cost);

    while(!feof (fileIn)) /* While o file still has numbers */
    {
        /* Read the input vals*/
        arrayEdges[numVertex].origNode = from;
        arrayEdges[numVertex].destNode = to;
        arrayEdges[numVertex].costEdge = cost;

        /* Update the existend nodes */
        groupNodes[from-1] = 1;
        groupNodes[to-1]   = 1;
        
        /* Try to read the next vals*/
        fscanf (fileIn, "%d", &from);
        fscanf (fileIn, "%d", &to);
        fscanf (fileIn, "%d", &cost);

        /*Count the real number of vertexes*/
        numVertex++;
    }

    /* Calculate the real number of nodes */
    for(i=0; i<100; i++)
        numNodes+=groupNodes[i];

    /* Close file, and zering pointer*/
    fclose(fileIn);
    fileIn=0;
}

void mergeEdges(int start1, int end1, int start2, int end2)
{
    int originalStart = start1;
    int size = end2 - start1;

    for(i=0; i<size; i++)
    {
        if(end1-start1==0) /* The array1 it's over */
        {
            tempArray[i]=arrayEdges[start2];
            start2++;
        }
        else
        {
            if(end2-start2==0) /* The array2 it's over */
            {
                tempArray[i]=arrayEdges[start1];
                start1++;
            }
            else
            {
                /* Has two, array1 and array2, and chose the less */
                if(arrayEdges[start1].costEdge>arrayEdges[start2].costEdge)
                {
                    tempArray[i]=arrayEdges[start2];
                    start2++;
                }
                else
                {
                    tempArray[i]=arrayEdges[start1];
                    start1++;
                }
            }
        }
    }

    /* Write temp array to the original array */
    for(i=0; i<size; i++)
        arrayEdges[originalStart+i]=tempArray[i];
}

void sortEdges(int start, int end)
{
    /* calcule the point to split the array */
    int midle = (int)((double)(end-start)/2.0) + start;

    /* if the array has more than one position, split again */
    if(end-start>1)
    {
        /* Sort the first part, the second part and merge */
        sortEdges(start, midle);
        sortEdges(midle, end);
        mergeEdges(start, midle, midle, end);
    }
}

void printArray()
{
    for(j=0; j<numNodes; j++)
        printf("%d -> %d | ",(j+1),groupNodes[j]);
}

void kruskal()
{
    int orig, dest, cost, from, to, count=0;;

    for(i=0; i<numVertex && count<(numNodes-1); i++) /* For now! it only needs up to number of cities */
    {
        printArray();

        orig = arrayEdges[i].origNode;
        dest = arrayEdges[i].destNode;
        cost = arrayEdges[i].costEdge;

        /* Take the less city id as from and the biger as to */
        if(groupNodes[orig-1] > groupNodes[dest-1])
        {
            from = groupNodes[dest-1];
            to   = groupNodes[orig-1];
        }
        else
        {
            to   = groupNodes[dest-1];
            from = groupNodes[orig-1];
        }

        printf("\t(%d, %d)\t|\t%d\t|", orig, dest, cost);

        /* If the edge connect tow diferents groups */
        if(from!=to)
        {
            for(j=0; j<100; j++)
            {
                if(groupNodes[j-1] == to)
                    groupNodes[j-1] = from;
            }
            count++;
            printf("Verdadeira\n");
        }
        else
        {
            printf("Falsa\n");
        }
    }
}

int main(int argc, char *argv[])
{
    char* inputFileName;

    /* Call to the initialize met*/
    initialize();

    /* Correct number of parameters? */
    if(argc<2)
    {
        printf("Incorrect number of parameters!\n");
        return 1;
    }
    inputFileName  = argv[1];
    readInputFile(inputFileName);

    /* Put every city in a group */
    for(i=0;i<100;i++)
        groupNodes[i]=(i+1);

    /* Processing */
    sortEdges(0,numVertex);
    kruskal();

    return 0;
}
