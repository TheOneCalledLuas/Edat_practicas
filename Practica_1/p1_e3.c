#include <stdlib.h>
#include <stdio.h>

#include "graph.h"

int main(int argc, char *argv[])
{

    FILE *file = NULL;
    Graph *graph = NULL;

    /*Checks that a file name was given to print the output.*/
    if (argc < 2)
    {
        printf("Wrong usage. please provide a file name as a parameter.\n");
        return 1;
    }

    /*Tries to open the file.*/
    if (!(file = fopen(argv[1], "r")))
    {
        printf("error while opening the file.");
        return 0;
    }

    /*Graph initialisation.*/
    if (!(graph = graph_init()))
    {
        printf("Error while creating the graph.");
        fclose(file);
        return 1;
    }

    /*Loads the graph from the file.*/
    if (!(graph_readFromFile(file, graph)))
    {
        printf("Error while creating the graph from the file.");
        fclose(file);
        graph_free(graph);
        return 1;
    }

    /*CLoses the file.*/
    fclose(file);

    /*Prints the graph.*/
    if (graph_print(stdout, graph) == -1)
    {
        printf("Error while printing the graph.");
    }

    /*Frees the graph.*/
    graph_free(graph);

    /*Clean exit.*/
    return 0;
}