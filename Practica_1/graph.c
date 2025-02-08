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
 * Private functions
 */

/* Get the position of the array where the vertex is store*/
int graph_get_vertex_at_with_id(Graph *g, long id);

int graph_get_vertex_at_with_tag(Graph *g, char *tag);

/**
 * Implementation of public functions
 */

Graph *graph_init()
{
    Graph *graph;

    /* Allocates memory for the graph with calloc, so the graph is initializated empty automatically*/
    if (!(graph = (Graph *)calloc(1, sizeof(Graph))))
    {
        return NULL;
    }

    return graph;
}

void graph_free(Graph *g)
{
    int i;

    if (g)
    {
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

    if (!g || !desc)
    {
        return ERROR;
    }

    if (!(vertex = vertex_initFromString(desc)))
    {
        return ERROR;
    }

    id_vertex = vertex_getId(vertex);

    for (i = 0; i < g->num_vertices; i++)
    {
        if (vertex_getId(g->vertices[i]) == id_vertex)
        {
            vertex_free(vertex);

            return ERROR;
        }
    }

    g->vertices[g->num_vertices] = vertex;
    (g->num_vertices)++;

    return OK;
}

Status graph_newEdge(Graph *g, long orig, long dest)
{
    int position_vertex_orig, position_vertex_dest, i, id_aux;

    if (!g)
    {
        return ERROR;
    }

    if ((position_vertex_dest = graph_get_vertex_at_with_id(g, dest)) < 0 || (position_vertex_orig = graph_get_vertex_at_with_id(g, orig)) < 0)
    {
        return ERROR;
    }

    g->connections[position_vertex_orig][position_vertex_dest] = TRUE;
    g->num_edges++;

    return OK;
}

Bool graph_contains(const Graph *g, long id)
{
    long position_vertex;

    if (!g)
    {
        return FALSE;
    }

    if ((position_vertex = graph_get_vertex_at_with_id(g, id)) < 0)
    {
        return FALSE;
    }

    return TRUE;
}

int graph_getNumberOfVertices(const Graph *g)
{
    if (!g)
    {
        return -1;
    }

    return g->num_vertices;
}

int graph_getNumberOfEdges(const Graph *g)
{
    if (!g)
    {
        return -1;
    }

    return g->num_edges;
}

Bool graph_connectionExists(const Graph *g, long orig, long dest)
{
    int i;

    if (!g || graph_contains(g, orig) == FALSE || graph_contains(g, dest) == FALSE)
    {
        return FALSE;
    }

    return g->connections[graph_get_vertex_at_with_id(g, orig)][graph_get_vertex_at_with_id(g, dest)];
}

int graph_getNumberOfConnectionsFromId(const Graph *g, long id)
{
    int n_connections, i, position_vertex;

    if (!g || graph_contains(g, id) == FALSE)
    {
        return -1;
    }

    position_vertex = graph_get_vertex_at_with_id(g, id);

    for (i = 0, n_connections = 0; i < g->num_vertices; i++)
    {
        if (g->connections[position_vertex][i] == TRUE)
        {
            n_connections++;
        }
    }

    return n_connections;
}

long *graph_getConnectionsFromId(const Graph *g, long id)
{
    long *vertex_connected;
    int i, position_vertex, n_connections, j;

    if (!g || graph_contains(g, id) == FALSE)
    {
        return NULL;
    }

    if ((n_connections = graph_getNumberOfConnectionsFromId(g, id)) < 0)
    {
        return NULL;
    }

    if (!(vertex_connected = malloc(n_connections * sizeof(long))))
    {
        return NULL;
    }

    position_vertex = graph_get_vertex_at_with_id(g, id);

    for (i = 0, j = 0; i < n_connections; i++)
    {
        if (g->connections[position_vertex][i] == TRUE)
        {
            vertex_connected[j] = vertex_getId(g->vertices[i]);
            j++;
        }
    }

    return vertex_connected;
}

int graph_getNumberOfConnectionsFromTag(const Graph *g, char *tag)
{
    int vertex_position, n_connections;

    if (!g || !tag || (vertex_position = graph_get_vertex_at_with_tag(g, tag)) < 0)
    {
        return -1;
    }

    return graph_getNumberOfConnectionsFromId(g, vertex_getId(g->vertices[vertex_position]));
}

long *graph_getConnectionsFromTag(const Graph *g, char *tag)
{
    int vertex_position;

    if (!g || !tag || (vertex_position = graph_get_vertex_at_with_tag(g, tag)) < 0)
    {
        return NULL;
    }

    return graph_getConnectionsFromId(g, vertex_getId(g->vertices[vertex_position]));
}

int graph_print(FILE *pf, const Graph *g)
{
    long *vertex_connected;
    long n_connections, n_characters = 0, aux;
    int i, j;

    if (!pf || !g)
    {
        return -1;
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        aux = vertex_print(pf, (void *)g->vertices[i]);
        if (aux < 0)
        {
            return -1;
        }

        n_characters += aux;
        n_characters += fprintf(pf, ": ");

        if ((vertex_connected = graph_getConnectionsFromId(g, vertex_getId(g->vertices[i]))))
        {
            n_connections = graph_getNumberOfConnectionsFromId(g, vertex_getId(g->vertices[i]));
            for (j = 0; i < n_connections; j++)
            {
                /* No compruebo el resultado de la funcion graph_get_vertex_at_with_id, ya que si el program ha llegado hasta aqui es que el puntero esta bien y que existe el id de vertex*/
                aux = vertex_print(pf, (void *)(g->vertices[graph_get_vertex_at_with_id(g, vertex_connected[j])]));
                if (aux < 0)
                {
                    return -1;
                }

                n_characters += aux;
            }
        }

        n_characters += fprintf(pf, "\n");
    }

    return n_characters;
}

Status graph_readFromFile(FILE *fin, Graph *g)
{
    int n_vertices, i;
    char str[MAX_WORD];
    long id_orig, id_dest;

    if (!fin || !g)
    {
        return ERROR;
    }

    fscanf(fin, "%d", n_vertices);

    for (i = 0; i < n_vertices; i++)
    {
        fgets(str, MAX_WORD, fin);

        if (graph_newVertex(g, str) == ERROR)
        {
            return ERROR;
        }
    }

    while (fscanf(fin, "%ld %ld", id_orig, id_dest) == 2)
    {
        if (graph_newEdge(g, id_orig, id_dest) == ERROR)
        {
            return ERROR;
        }
    }

    return OK;
}

/**
 * Implementation of private functions
 */

int graph_get_vertex_at_with_id(Graph *g, long id)
{
    int i, position_vertex = -1;
    long id_aux;

    if (!g)
    {
        return -1; /* Error code*/
    }

    for (i = 0; i < g->num_vertices; i++)
    {
        id_aux = vertex_getId(g->vertices[i]);

        if (id_aux == id)
        {
            position_vertex = i;
        }
    }

    return position_vertex;
}

int graph_get_vertex_at_with_tag(Graph *g, char *tag)
{
    int i, vertex_position = -1;

    for (i = 0; i < g->num_vertices; i++)
    {
        if (!strcmp(vertex_getTag(g->vertices[i]), tag))
        {
            vertex_position = i;
        }
    }

    return vertex_position;
}