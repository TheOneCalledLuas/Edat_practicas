#include "graph.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct _Graph
{
    Vertex *vertices[MAX_VTX];
    Bool connections[MAX_VTX][MAX_VTX];
    int num_vertices;
    int num_edges;
};

/**
 * Private functions.
 */

/* Gets the position of the array where the vertex is stored  by using the id.*/
int graph_getVertexAtWithId(const Graph *g, long id);

/* Gets the position of the array where the vertex is stored  by using the tag.*/
int graph_getVertexAtWithTag(const Graph *g, char *tag);

/**
 * Implementation of public functions
 */

Graph *graph_init()
{
    Graph *graph;

    /* Memory allocacion.*/
    if (!(graph = (Graph *)calloc(1, sizeof(Graph))))
    {
        return NULL;
    }

    return graph;
}

void graph_free(Graph *g)
{
    int i;

    /* Tries to free the structure, if it exists.*/
    if (g)
    {
        /*Frees each vertex.*/
        for (i = 0; i < g->num_vertices; i++)
        {
            vertex_free(g->vertices[i]);
        }
        free(g);
    }
}

Status graph_newVertex(Graph *g, char *desc)
{
    Vertex *vertex;
    int i;
    long id_vertex;

    /* Checks the parameters.*/
    if (!g || !desc)
    {
        return ERROR;
    }

    /* Tries to read the vertex information.*/
    if (!(vertex = vertex_initFromString(desc)))
    {
        return ERROR;
    }

    /* Asures that there's no vertex with the same id.*/
    id_vertex = vertex_getId(vertex);
    for (i = 0; i < g->num_vertices; i++)
    {
        /*  If its repeated frees the memory and raises and error.*/
        if (vertex_getId(g->vertices[i]) == id_vertex)
        {
            vertex_free(vertex);

            return ERROR;
        }
    }
    /* Adds the vertex to the graph.*/
    g->vertices[g->num_vertices] = vertex;
    (g->num_vertices)++;

    return OK;
}

Status graph_newEdge(Graph *g, long orig, long dest)
{
    int position_vertex_orig, position_vertex_dest;

    /* Checks the parameters (pointers and Ids).*/
    if (!g)
    {
        return ERROR;
    }

    if ((position_vertex_dest = graph_getVertexAtWithId(g, dest)) < 0 || (position_vertex_orig = graph_getVertexAtWithId(g, orig)) < 0)
    {
        return ERROR;
    }

    /* Adds the edge.*/
    g->connections[position_vertex_orig][position_vertex_dest] = TRUE;
    g->num_edges++;

    /* Clean exit.*/
    return OK;
}

Bool graph_contains(const Graph *g, long id)
{
    long position_vertex;
    /* Checks the parameters.*/
    if (!g)
    {
        return FALSE;
    }
    /* Searches for a vertex with that id.*/
    if ((position_vertex = graph_getVertexAtWithId(g, id)) < 0)
    {
        return FALSE;
    }

    return TRUE;
}

int graph_getNumberOfVertices(const Graph *g)
{
    /* Error management.*/
    if (!g)
    {
        return -1;
    }

    /* Returns the value.*/
    return g->num_vertices;
}

int graph_getNumberOfEdges(const Graph *g)
{
    /* Error management.*/
    if (!g)
    {
        return -1;
    }

    /* Returns the value.*/
    return g->num_edges;
}

Bool graph_connectionExists(const Graph *g, long orig, long dest)
{
    /* Error management.*/
    if (!g || graph_contains(g, orig) == FALSE || graph_contains(g, dest) == FALSE)
    {
        return FALSE;
    }
    /* Returns the stored value which regards the conection between such vertex.*/
    return g->connections[graph_getVertexAtWithId((Graph *)g, orig)][graph_getVertexAtWithId((Graph *)g, dest)];
}

int graph_getNumberOfConnectionsFromId(const Graph *g, long id)
{
    int n_connections, i, position_vertex;

    /* Error management.*/
    if (!g || graph_contains(g, id) == FALSE)
    {
        return -1;
    }

    /* Gets the vertex Id.*/
    position_vertex = graph_getVertexAtWithId(g, id);

    /* Countts the number of edges.*/
    for (i = 0, n_connections = 0; i < g->num_vertices; i++)
    {
        if (g->connections[position_vertex][i] == TRUE)
        {
            n_connections++;
        }
    }
    /* Returns the count.*/
    return n_connections;
}

long *graph_getConnectionsFromId(const Graph *g, long id)
{
    long *vertex_connected;
    int i, position_vertex, n_connections, j;

    /* Checks the parameters.*/
    if (!g || graph_contains(g, id) == FALSE)
    {
        return NULL;
    }

    if ((n_connections = graph_getNumberOfConnectionsFromId(g, id)) < 0)
    {
        return NULL;
    }
    /* Allocates memory.*/
    if (!(vertex_connected = malloc(n_connections * sizeof(long))))
    {
        return NULL;
    }

    /* Gets the vertex's Id.*/
    position_vertex = graph_getVertexAtWithId(g, id);

    /* Adds the Vertex's Id of the ones connected to this one.*/
    for (i = 0, j = 0; j < n_connections; i++)
    {
        if (g->connections[position_vertex][i] == TRUE)
        {
            vertex_connected[j] = vertex_getId(g->vertices[i]);
            j++;
        }
    }
    /* Returns the value.*/
    return vertex_connected;
}

int graph_getNumberOfConnectionsFromTag(const Graph *g, char *tag)
{
    int vertex_position;

    /* Error management.*/
    if (!g || !tag || (vertex_position = graph_getVertexAtWithTag(g, tag)) < 0)
    {
        return -1;
    }
    /* Searches the result by the id.*/
    return graph_getNumberOfConnectionsFromId(g, vertex_getId(g->vertices[vertex_position]));
}

long *graph_getConnectionsFromTag(const Graph *g, char *tag)
{
    int vertex_position;

    /* Error management.*/
    if (!g || !tag || (vertex_position = graph_getVertexAtWithTag(g, tag)) < 0)
    {
        return NULL;
    }
    /* Searches the result by the id.*/
    return graph_getConnectionsFromId(g, vertex_getId(g->vertices[vertex_position]));
}

int graph_print(FILE *pf, const Graph *g)
{
    long *vertex_connected;
    long n_connections, n_characters = 0, aux;
    int i, j;

    /* Checks the arguments.*/
    if (!pf || !g)
    {
        return -1;
    }
    /* Prints the graph vertex by vertex.*/
    for (i = 0; i < g->num_vertices; i++)
    {
        /* Prints the vertex.*/
        aux = vertex_print(pf, (void *)g->vertices[i]);
        if (aux < 0)
        {
            return -1;
        }

        /* Adds the printed characters to the count.*/
        n_characters += aux;
        n_characters += fprintf(pf, ": ");

        /* Prints the vertices which are connected to this one.*/
        if ((vertex_connected = graph_getConnectionsFromId(g, vertex_getId(g->vertices[i]))))
        {
            n_connections = graph_getNumberOfConnectionsFromId(g, vertex_getId(g->vertices[i]));
            for (j = 0; j < n_connections; j++)
            {
                /* Prints each vertex if everything goes as it should.*/
                aux = vertex_print(pf, (void *)(g->vertices[graph_getVertexAtWithId(g, vertex_connected[j])]));
                fprintf(pf, " ");
                if (aux < 0)
                {
                    return -1;
                }
                /* Adds the printed characetrs to the count.*/
                n_characters += aux + 1;
            }
        }
        /* Frees the temporal structure.*/
        free(vertex_connected);

        /* Adds the line jump.*/
        n_characters += fprintf(pf, "\n");
    }
    /* Returns the printed characters.*/
    return n_characters;
}

Status graph_readFromFile(FILE *fin, Graph *g)
{
    int n_vertices, i;
    char str[MAX_WORD];
    long id_orig, id_dest;

    /* Error management.*/
    if (!fin || !g)
    {
        return ERROR;
    }

    /* Reads the number of vertex in the graph.*/
    fscanf(fin, "%d", &n_vertices);

    /* Skips the rest of the first line.*/
    rewind(fin);
    fgets(str, MAX_WORD, fin);

    /* Loads all the vertices.*/
    for (i = 0; i < n_vertices; i++)
    {
        fgets(str, MAX_WORD, fin);

        if (graph_newVertex(g, str) == ERROR)
        {
            return ERROR;
        }
    }
    /* Loads all the edges.*/
    while (fscanf(fin, "%ld %ld", &id_orig, &id_dest) == 2)
    {
        if (graph_newEdge(g, id_orig, id_dest) == ERROR)
        {
            return ERROR;
        }
    }

    return OK;
}

/**
 * Implementation of private functions.
 */

int graph_getVertexAtWithId(const Graph *g, long id)
{
    int i, position_vertex = -1;
    long id_aux;

    /* Error management.*/
    if (!g)
    {
        return -1; /* Error code*/
    }

    /* Searches for the vertex.*/
    for (i = 0; i < g->num_vertices; i++)
    {
        id_aux = vertex_getId(g->vertices[i]);

        if (id_aux == id)
        {
            /* If found, it is assigned.*/
            position_vertex = i;
        }
    }
    /* Returns the position.*/
    return position_vertex;
}

int graph_getVertexAtWithTag(const Graph *g, char *tag)
{
    int i, vertex_position = -1;

    /* Searches for the vertex.*/
    for (i = 0; i < g->num_vertices; i++)
    {
        if (!strcmp(vertex_getTag(g->vertices[i]), tag))
        {
            /* If found, the id is asigned so that it is returned.*/
            vertex_position = i;
        }
    }
    /* Returns the value.*/
    return vertex_position;
}