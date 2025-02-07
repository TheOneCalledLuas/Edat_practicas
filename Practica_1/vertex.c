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

/*----------------------------------------------------------------------------------------*/
/*
Private function:
*/
Status vertex_setField(Vertex *v, char *key, char *value);
Vertex *vertex_initFromString(char *descr);

Status vertex_setField(Vertex *v, char *key, char *value)
{
    if (!key || !value)
        return ERROR;

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

/*----------------------------------------------------------------------------------------*/
Vertex *vertex_initFromString(char *descr)
{
    char buffer[1024];
    char *token;
    char *key;
    char *value;
    char *p;
    Vertex *v;

    /* Check args: */
    if (!descr)
        return NULL;

    /* Allocate memory for vertex: */
    v = vertex_init();
    if (!v)
        return NULL;

    /* Read and tokenize description: */
    sprintf(buffer, "%s", descr);
    token = strtok(buffer, " \t\n");
    while (token)
    {
        p = strchr(token, ':');
        if (!p)
            continue;

        *p = '\0';
        key = token;
        value = p + 1;

        vertex_setField(v, key, value);

        token = strtok(NULL, " \t\n");
    }

    return v;
}

/**  rest of the functions in vertex.h **/
Vertex *vertex_init()
{
    /*Memory allocation.*/
    Vertex *vertex = (Vertex *)malloc(sizeof(Vertex));

    /*Set the values to default state.*/
    if (vertex)
    {
        vertex->id = 0;
        vertex->state = WHITE;
        vertex->tag[0] = '\0';
    }

    /*Returns the pointer.*/
    return vertex;
}

Vertex *vertex_initFromString(char *descr)
{
    char *token;
    int i;
    Vertex *vertex;

    /*Control error*/
    if (!descr || !(vertex = vertex_init()))
    {
        return NULL;
    }

    /*It took the first part of the string*/
    token = strtok(descr, ':');
    while (token != NULL) /* stop when the string has end*/
    {
        /*compere the part of the string, and in function of his name, it stores his value in the right field*/
        if (!strcmp(token, "id"))
        {
            token = strtok(NULL, ':');
            vertex->id = atol(token);
        }
        else if (!strcmp(token, "tag"))
        {
            token = strtok(NULL, ':');
            strcpy(vertex->tag, token);
        }
        else if (!strcmp(token, "state"))
        {
            token = strtok(NULL, ':');
            vertex->state = token;
        }

        token = strtok(NULL, ':');
    }

    return vertex;
}

void vertex_free(void *v)
{
    /*Checks that the pointer isn't NULL and free it.*/
    if (v)
    {
        free(v);
    }
}

long vertex_getId(const Vertex *v)
{
    /*Checks the parameters.*/
    if (!v)
    {
        return -1;
    }
    /*Returns the value.*/
    return v->id;
}

Label vertex_getState(const Vertex *v)
{
    /*Checks the parameters.*/
    if (!v)
    {
        return -1;
    }
    /*Returns the value.*/
    return v->state;
}

Status vertex_setId(Vertex *v, const long id)
{
    /*Checks the prameters.*/
    if (!v || id < 0)
    {
        return ERROR;
    }
    /*Sets the value.*/
    v->id = id;

    /*Clean exit.*/
    return OK;
}

Status vertex_setTag(Vertex *v, const char *tag)
{
    /*Checks the parameters.*/
    if (!v || !tag || strlen(tag) > TAG_LENGTH)
    {
        return ERROR;
    }

    /*Sets the tag.*/
    strcpy(v->tag, tag);

    /*Clean exit.*/
    return OK;
}

Status vertex_setState(Vertex *v, const Label state)
{
    /*Checks the parameters.*/
    if (!v)
    {
        return ERROR;
    }
    /*Sets the value.*/
    v->state = state;

    /*Clean exit.*/
}

int vertex_cmp(const void *v1, const void *v2)
{
    Vertex * 
    /*Checks the parameters.*/
    if (!v1 || !v2)
    {
        return 0;
    }
    /*Compares the id.*/
    if (v1->id == v2->id)
    {
        /*Compares the tags.*/
        return strcmp(v1->tag, v2->tag);
    }
    else
    {
        /*Returns the id difference.*/
        return (v1->id) - (v2->id);
    }
}

void *vertex_copy(const void *src)
{
    void *vertex;

    if (!src)
    {
        return NULL;
    }

    return vertex;
};

int vertex_print(FILE *pf, const void *v)
{
    /*Checks the parameters.*/
    if (!pf || !v)
    {
        return -1;
    }
    /*Printts the information in the file.*/
    fprintf(pf, "[%ld, %s, %d]", v->id, v->tag, v->state);

    /*Clean exit*/
}
