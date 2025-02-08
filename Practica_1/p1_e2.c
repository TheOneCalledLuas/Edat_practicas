#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
    Graph *graph;
    int n_connections, i;
    long *connections;

    if (!(graph = graph_init()))
    {
        fprintf(stdout, "There has been an error initializating the graph\n");

        return 1;
    }

    fprintf(stdout, "Inserting Madrid... result...: ");
    if (graph_newVertex(graph, "tag:Madrid id:111 state:WHITE") == ERROR)
    {
        fprintf(stdout, "0, there has been an error\n");
        graph_free(graph);

        return 1;
    }
    fprintf(stdout, "1\n");

    fprintf(stdout, "Inserting Toledo...result...: ");
    if (graph_newVertex(graph, "tag:Toledo id:222 state:WHITE") == ERROR)
    {
        fprintf(stdout, "0, there has been an error\n");
        graph_free(graph);

        return 1;
    }
    fprintf(stdout, "1\n");

    fprintf(stdout, "Inserting edge: 222 --> 111\n");
    if (graph_newEdge(graph, 222, 111) == ERROR)
    {
        fprintf(stdout, "There has been an error\n");
        graph_free(graph);

        return 1;
    }

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

    fprintf(stdout, "Number of connections from 111: ");
    if ((n_connections = graph_getNumberOfConnectionsFromId(graph, 111)) < 0)
    {
        fprintf(stdout, "There has been an error\n");
        graph_free(graph);

        return 1;
    }
    fprintf(stdout, "%d\n", n_connections);

    fprintf(stdout, "Number of connections from Toledo: ");
    if ((n_connections = graph_getNumberOfConnectionsFromTag(graph, "Toledo")) < 0)
    {
        fprintf(stdout, "There has been an error\n");
        graph_free(graph);

        return 1;
    }
    fprintf(stdout, "%d\n", n_connections);

    fprintf(stdout, "Connections from Toledo: ");
    if (!(connections = graph_getConnectionsFromTag(graph, "Toledo")))
    {
        fprintf(stdout, "There has been an error\n");
        graph_free(graph);

        return 1;
    }

    for (i = 0; i < n_connections; i++)
    {
        fprintf(stdout, "%ld ", connections[i]);
    }
    fprintf(stdout, "\n");

    fprintf(stdout, "Graph: \n");
    if(graph_print(stdout, graph) < 0) {
        fprintf(stdout, "There has been an error\n");
    }

    graph_free(graph);
    free(connections);

    return 0;
}