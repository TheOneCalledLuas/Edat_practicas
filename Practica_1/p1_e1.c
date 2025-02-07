#include "vertex.h"

#include <stdio.h>

int main()
{
    Vertex *vertex_1 = NULL, *vertex_2 = NULL;
    void *vertex_3 = NULL;

    /*Init vertex_1*/
    if (!(vertex_1 = vertex_init())) /*Checks that the pointer isn't equal to NULL*/
    {
        return 1; /*error code*/
    }

    /*Init vertex_2*/
    if (!(vertex_2 = vertex_init())) /*Checks that the pointer isn't equal to NULL*/
    {
        vertex_free((void *)vertex_1);

        return 1; /*error code*/
    }

    /*Set the vertex_1 to the arguments indicated*/
    if (vertex_setId(vertex_1, 10) == ERROR || vertex_setState(vertex_1, WHITE) == ERROR || vertex_setTag(vertex_1, "one") == ERROR) /* Control error*/
    {
        /*free the allocated memory in case of error*/
        vertex_free((void *)vertex_1);
        vertex_free((void *)vertex_2);

        return 1; /*error code*/

    }

    /*Set the vertex_2 to the arguments indicated*/
    if (vertex_setId(vertex_2, 20) == ERROR || vertex_setState(vertex_2, BLACK) == ERROR || vertex_setTag(vertex_2, "two") == ERROR) /* Control error*/
    {
        /*free the allocated memory in case of error*/
        vertex_free((void *)vertex_1);
        vertex_free((void *)vertex_2);

        return 1; /*error code*/

    }

    /* Print the vertex_1 and vertex_2*/
    if (vertex_print(stdout, (void *)vertex_1) == -1 || vertex_print(stdout, (void *)vertex_2) == -1) /* Control error*/
    {
        /*free the allocated memory in case of error*/
        vertex_free((void *)vertex_1);
        vertex_free((void *)vertex_2);

        return 1; /*error code*/

    }
    fprintf(stdout, "\n");

    /* Compare both vertex*/
    fprintf(stdout, "Equals? ");
    if (!vertex_cmp((void *)vertex_1, (void *)vertex_2))
    {
        fprintf(stdout, "Yes\n"); /* Equals*/
    }
    else
    {
        fprintf(stdout, "No\n"); /* Not equals*/
    }

    /* Print the tag of Vertex 2*/
    fprintf(stdout, "Vertex 2 tag: %s\n", vertex_getTag(vertex_2));

    /* Copy vertex_1 into the vertex_3*/
    if (!(vertex_3 = vertex_copy((void *)vertex_1)))
    {
        /*free the allocated memory in case of error*/
        vertex_free((void *)vertex_1);
        vertex_free((void *)vertex_2);

        return 1; /*error code*/
    }

    /* Print the id of vertex_3*/
    fprintf(stdout, "Vertex 3 id: %ld\n", vertex_getId((Vertex *)vertex_3));

    /* Print the vertex_1 and vertex_3*/
    if (vertex_print(stdout, (void *)vertex_1) == -1 || vertex_print(stdout, vertex_3) == -1) /* Control error*/
    {
        /*free the allocated memory in case of error*/
        vertex_free((void *)vertex_1);
        vertex_free((void *)vertex_2);
        vertex_free(vertex_3);

        return 1; /*error code*/
    }

    /* Compare both vertex*/
    fprintf(stdout, "\nEquals? ");
    if (!vertex_cmp((void *)vertex_1, vertex_3))
    {
        fprintf(stdout, "Yes\n"); /* Equals*/
    }
    else
    {
        fprintf(stdout, "No\n"); /* Not equals*/
    }

    /* Free all the allocated memory*/
    vertex_free((void *)vertex_1);
    vertex_free((void *)vertex_2);
    vertex_free(vertex_3);

    return 0;
}