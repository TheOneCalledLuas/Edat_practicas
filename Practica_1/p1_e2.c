#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    Graph *graph;
    int n_connections, i;
    long *connections;

    /* Graph initialisation.*/
    if (!(graph = graph_init()))
    {
        fprintf(stdout, "There has been an error initializating the graph\n");

        return 1;
    }

    /* Inserts Madrid's vertex.*/
    fprintf(stdout, "Inserting Madrid... result...: ");
    if (graph_newVertex(graph, "tag:Madrid id:111 state:WHITE") == ERROR)
    {
        /* If an error occurs.*/
        fprintf(stdout, "0, there has been an error\n");
        graph_free(graph);

        return 1;
    }
    fprintf(stdout, "1\n");

    /* Inserts Toledo's vertex.*/
    fprintf(stdout, "Inserting Toledo...result...: ");
    if (graph_newVertex(graph, "tag:Toledo id:222 state:WHITE") == ERROR)
    {
        /* If an error occurs.*/
        fprintf(stdout, "0, there has been an error\n");
        graph_free(graph);

        return 1;
    }
    fprintf(stdout, "1\n");

    /* Inserts the edge between them.*/
    fprintf(stdout, "Inserting edge: 222 --> 111\n");
    if (graph_newEdge(graph, 222, 111) == ERROR)
    {
        /* If an error occurs.*/
        fprintf(stdout, "There has been an error\n");
        graph_free(graph);

        return 1;
    }

    /* Checks if the vertex exists.*/
    fprintf(stdout, "111 --> 222? ");
    switch (graph_connectionExists(graph, 111, 222))
    {
    case TRUE:
        fprintf(stdout, "Yes\n");
        break;

    case FALSE:
        fprintf(stdout, "No\n");
        break;
    }

    /* Checks the edge the other way around.*/
    fprintf(stdout, "222 --> 111? ");
    switch (graph_connectionExists(graph, 222, 111))
    {
    case TRUE:
        fprintf(stdout, "Yes\n");
        break;

    case FALSE:
        fprintf(stdout, "No\n");
        break;
    }

    /* Prints the number of connections of the vertex with id 111.*/
    fprintf(stdout, "Number of connections from 111: ");
    if ((n_connections = graph_getNumberOfConnectionsFromId(graph, 111)) < 0)
    {
        /* If an error occurs.*/
        fprintf(stdout, "There has been an error\n");
        graph_free(graph);

        return 1;
    }
    fprintf(stdout, "%d\n", n_connections);

    /* Prints the number of connections of the vertex with tag Toledo.*/
    fprintf(stdout, "Number of connections from Toledo: ");
    if ((n_connections = graph_getNumberOfConnectionsFromTag(graph, "Toledo")) < 0)
    {
        /* If an error occurs.*/
        fprintf(stdout, "There has been an error\n");
        graph_free(graph);

        return 1;
    }
    fprintf(stdout, "%d\n", n_connections);

    /* Prints the id's of the connections with Toledo.*/
    fprintf(stdout, "Connections from Toledo: ");
    if (!(connections = graph_getConnectionsFromTag(graph, "Toledo")))
    {
        /* If an error occurs.*/
        fprintf(stdout, "There has been an error\n");
        graph_free(graph);

        return 1;
    }
    /* Shows the connections.*/
    for (i = 0; i < n_connections; i++)
    {
        fprintf(stdout, "%ld ", connections[i]);
    }
    fprintf(stdout, "\n");

    /* Prints the graph.*/
    fprintf(stdout, "Graph: \n");
    if (graph_print(stdout, graph) < 0)
    {
        /* If an error occurs.*/
        fprintf(stdout, "There has been an error\n");
    }

    /* Frees the used memory.*/
    graph_free(graph);
    free(connections);

    /* Clean exit.*/
    return 0;
}