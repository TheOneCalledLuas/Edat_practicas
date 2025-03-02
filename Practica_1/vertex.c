/**
 * @file  vertex.c
 * @authors Héctor García y Saúl López
 * @date 8 February 2025
 * @version 1.0
 * @brief Implementacion of vertex.h
 *
 * @details
 *
 * @see
 */

#include "vertex.h"
#include <string.h>

#define TAG_LENGTH 64

/**
 * @brief Vertex structure.
 */
struct _Vertex
{
    long id;              /* !< id of vertex*/
    char tag[TAG_LENGTH]; /* !< */
    Label state;          /* !< state of type label*/
};


/*
Private function:
*/

/**
 * @brief Help the function vertex_initFromString to set each field of the vertex's struct.
 *
 * @param v Pointer to the vertex.
 * @param key Pointer to the name of the field we would like to set.
 * @param value Pointer to the value.
 * 
 * @return Return ERROR if there was an error, OK otherwise.
 */
Status vertex_setField(Vertex *v, char *key, char *value)
{
    /* Checks the parameters.*/
    if (!key || !value)
        return ERROR;

    /* Finds and sets the field we want to set.*/
    if (strcmp(key, "id") == 0)
    {
        return vertex_setId(v, atol(value));
    }
    else if (strcmp(key, "tag") == 0)
    {
        return vertex_setTag(v, value);
    }
    else if (strcmp(key, "state") == 0)
    {
        return vertex_setState(v, (Label)atoi(value));
    }

    return ERROR;
}

/**  
Rest of the functions in vertex.h
*/

/* Initialize a vertex.*/
Vertex *vertex_init()
{
    /* Memory allocation.*/
    Vertex *vertex = (Vertex *)malloc(sizeof(Vertex));

    /* Set the values to default state.*/
    if (vertex)
    {
        vertex->id = 0;
        vertex->state = WHITE;
        vertex->tag[0] = '\0';
    }

    /* Returns the pointer.*/
    return vertex;
}

/* Initialize a vertex from its description.*/
Vertex *vertex_initFromString(char *descr)
{
    char buffer[1024];
    char *token;
    char *key;
    char *value;
    char *p;
    Vertex *v;

    /* Check args.*/
    if (!descr)
        return NULL;

    /* Allocate memory for vertex.*/
    v = vertex_init();
    if (!v)
        return NULL;

    /* Read and tokenize description.*/
    sprintf(buffer, "%s", descr);
    token = strtok(buffer, " \t\n");
    while (token)
    {
        p = strchr(token, ':');
        if (!p)
        {
            token = strtok(NULL, " \t\n");
            continue;
        }

        *p = '\0';
        key = token;
        value = p + 1;

        vertex_setField(v, key, value);

        token = strtok(NULL, " \t\n");
    }

    return v;
}

/* Free the dynamic memory reserved for a vertex.*/
void vertex_free(void *v)
{
    /* Checks that the pointer isn't NULL and free it.*/
    if (v)
    {
        free(v);
    }
}

/* Gets the vertex id.*/
long vertex_getId(const Vertex *v)
{
    /* Checks the parameters.*/
    if (!v)
    {
        return -1;
    }

    /* Returns the value.*/
    return v->id;
}

/* Gets the vertex tag.*/
const char *vertex_getTag(const Vertex *v)
{
    /* Checks the parameters.*/
    if (!v)
    {
        return NULL;
    }

    /* Returns the value.*/
    return (void *)(v->tag);
}

/* Gets the state of a given vertex.*/
Label vertex_getState(const Vertex *v)
{
    /* Checks the parameters.*/
    if (!v)
    {
        return -1;
    }

    /* Returns the value.*/
    return v->state;
}

/* Modifies the id of a given vertex.*/
Status vertex_setId(Vertex *v, const long id)
{
    /* Checks the prameters.*/
    if (!v || id < 0)
    {
        return ERROR;
    }

    /* Sets the value.*/
    v->id = id;

    /* Clean exit.*/
    return OK;
}

/* Modifies the tag of a given vertex.*/
Status vertex_setTag(Vertex *v, const char *tag)
{
    /* Checks the parameters.*/
    if (!v || !tag || strlen(tag) > TAG_LENGTH)
    {
        return ERROR;
    }

    /* Sets the tag.*/
    strcpy(v->tag, tag);

    /* Clean exit.*/
    return OK;
}

/* Modifies the state of a given vertex.*/
Status vertex_setState(Vertex *v, const Label state)
{
    /* Checks the parameters.*/
    if (!v)
    {
        return ERROR;
    }

    /* Sets the value.*/
    v->state = state;

    /* Clean exit.*/
    return OK;
}

/* Compares two vertices.*/
int vertex_cmp(const void *v1, const void *v2)
{
    Vertex *vertex_1 = (Vertex *)v1;
    Vertex *vertex_2 = (Vertex *)v2;

    /* Checks the parameters.*/
    if (!v1 || !v2)
    {
        return 0;
    }

    /* Compares the id.*/
    if (vertex_1->id == vertex_2->id)
    {
        /* Compares the tags.*/
        return strcmp(vertex_1->tag, vertex_2->tag);
    }
    else
    {
        /* Returns the id difference.*/
        return (vertex_1->id) - (vertex_2->id);
    }
}

/* Reserves memory for a vertex where it copies the data from the vertex src.*/
void *vertex_copy(const void *src)
{
    Vertex *vertex;

    /* Checks the parameters.*/
    if (!src || !(vertex = vertex_init()))
    {
        return NULL;
    }

    /* Initializates each field of the new vertex.*/
    vertex->id = ((Vertex *)src)->id;
    strcpy(vertex->tag, ((Vertex *)src)->tag);
    vertex->state = ((Vertex *)src)->state;

    /* Return the point to the new vertex.*/
    return (void *)vertex;
}

/* Prints in pf the data of a vertex.*/
int vertex_print(FILE *pf, const void *v)
{
    Vertex *vertex_1 = (Vertex *)v;

    /* Checks the parameters.*/
    if (!pf || !v)
    {
        return -1;
    }

    /* Printts the information in the file.*/
    return fprintf(pf, "[%ld, %s, %d]", vertex_1->id, vertex_1->tag, vertex_1->state);
}
