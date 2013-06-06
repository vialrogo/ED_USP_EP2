/*
 * main.c            File with the functions for read the input files, the sort
 *                   method, auxiliar functions and main method with the calls 
 *                   to these functions.
 * Create by:        Victor Alberto Romero Gonzalez 
 *
 */

#include <stdio.h>
#include <math.h>

/* Structs definitions*/
struct _Edge
{
   int origNode;
   int destNode;
   int costEdge;
};
typedef struct _Edge Edge;

/* Global variables*/
int numVertex, numNodes;
Edge arrayEdges[10000]; /* Maximun number of edges */
Edge tempArray [10000]; /* Maximun number of edges */
int groupNodes[100];    /* Maximun number of cities */

/* Method definitions */
void initialize()
{
    int i;
    numVertex=0;
    numNodes=0;

    for(i=0;i<100;i++)
        groupNodes[i]=0;
}

void readInputFile(char* inputFileName)
{
    int i;
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
    int i;
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
    int i, j, numNodesPerGroup, totalNumberGroups=0, count;

    /* Common begin for all lines */
    printf("|  ");
    
    /* First calculate the total of groups in this iteration */
    for(i=0; i<numNodes; i++)
        for(j=0; j<numNodes; j++) 
            if(groupNodes[j]==(i+1))
            {
                totalNumberGroups++;
                j=numNodes;
            }

    /* count go to down, totalNumberGroups fix equal */
    count=totalNumberGroups;
 
    /* Going to try to print all possible groups */
    for(i=0; i<numNodes; i++)
    {
        numNodesPerGroup = 0;

        /* Calculate the total number of nodes in this group */
        for(j=0; j<numNodes; j++)
            if(groupNodes[j]==(i+1))
                numNodesPerGroup++;

        /* If have at least one node in this group */
        if(numNodesPerGroup>0)
        {
            printf("R%d{",(i+1));
            for(j=0; j<numNodes; j++) /* Try to print all nodes */
            {
                if(groupNodes[j]==(i+1)) /* Only print a node that is in this group */
                {
                    printf("%d",(j+1));
                    numNodesPerGroup--;
                
                    if(numNodesPerGroup!=0) /* Only if isn't the last group */
                        printf(", ");
                }
            }
            printf("}");
            count--;
            
            if(count!=0) /* Only if isn't the last group */
                printf(", ");
        }
    }

    /* Print the remain spaces for aline the output */
    for(i=0;i<(numNodes-totalNumberGroups);i++)
        printf("    ");
    
    /* Print the remain spaces for aline the output */
    for(i=0;i<(50-(5*numNodes+2*(numNodes-1)+1));i++)
        printf(" ");
}

void printDivision()
{
    int i;

    printf("+");
    for(i=0; i<(5*numNodes+2*(numNodes-1)+2) || i<51; i++)
        printf("-");
    
    printf("+----------------+---------+---------------------+\n");
}

void kruskal()
{
    int i, j, orig, dest, cost, from, to, count=0, space2;

    /* Print the first information */
    printDivision();

    printf("|  Coleção C (conjs. com vértices na mesma árvore)  ");
    for(i=0; i<((5*numNodes+2*(numNodes-1)+1)-50); i++) printf(" ");
    printf("|  aresta menor  |  custo  |  condição na linha  |\n");

    printDivision();

    /* Until haven't try all vertex AND not used n-1 vertex */
    for(i=0; i<numVertex && count<(numNodes-1); i++)
    {
        /* Print the array of groups */
        printArray();

        /* Save the original states */
        orig = arrayEdges[i].origNode;
        dest = arrayEdges[i].destNode;
        cost = arrayEdges[i].costEdge;

        /* Take the less city id as from and the biger as to */
        from = groupNodes[dest-1] > groupNodes[orig-1]?  groupNodes[orig-1] : groupNodes[dest-1];
        to   = groupNodes[dest-1] < groupNodes[orig-1]?  groupNodes[orig-1] : groupNodes[dest-1];

        /* Print the rest of the information */
        space2 = 0;
        space2 += log10((double)orig)+1.0;
        space2 += log10((double)dest)+1.0;

        printf("|   (%d, %d)   ",orig, dest);
        for(j=0;j<(6-space2);j++) printf(" ");        
        
        printf("|\t%d\t", cost);

        /* If the edge connect two DIFERENT groups */
        if(from!=to)
        {
            /* Update all groups with the new vals */
            for(j=0; j<100; j++)
            {
                if(groupNodes[j] == to)
                    groupNodes[j] = from;
            }
            count++;
            printf( "|      Verdadeira     |\n");
        }
        else
        {
            printf( "|        Falsa        |\n");
        }
    }

    /* Print the final information */
    printArray();
    printf("|                |\t\t|\n");
    printDivision();
}

int main(int argc, char *argv[])
{
    int i;
    char* inputFileName;

    /* Call to the initialize method */
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
