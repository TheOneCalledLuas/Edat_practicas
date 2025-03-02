#include "vertex.h"

#include <stdio.h>

int main()
{
    Vertex *vertex_1 = NULL, *vertex_2 = NULL;
    void *vertex_3 = NULL;

    /* Iniializates and checks vertex_1.*/
    if (!(vertex_1 = vertex_init()))
    {
        fprintf(stdout, "There has been an error initializating the vertex 1\n");
        return 1;
    }

    /* Iniializates and checks vertex_2.*/
    if (!(vertex_2 = vertex_init()))
    {
        /* Free the allocated memory in case of error.*/
        vertex_free((void *)vertex_1);

        fprintf(stdout, "There has been an error initializating the vertex 2\n");
        return 1;
    }

    /* Sets the vertex_1 to the arguments indicated.*/
    if (vertex_setId(vertex_1, 10) == ERROR || vertex_setState(vertex_1, WHITE) == ERROR || vertex_setTag(vertex_1, "one") == ERROR) /* Control error*/
    {
        /* Free the allocated memory in case of error.*/
        vertex_free((void *)vertex_1);
        vertex_free((void *)vertex_2);

        fprintf(stdout, "There has been an error setting the vertex 1\n");
        return 1;
    }

    /* Sets the vertex_2 to the arguments indicated.*/
    if (vertex_setId(vertex_2, 20) == ERROR || vertex_setState(vertex_2, BLACK) == ERROR || vertex_setTag(vertex_2, "two") == ERROR) /* Control error*/
    {
        /* Free the allocated memory in case of error.*/
        vertex_free((void *)vertex_1);
        vertex_free((void *)vertex_2);

        fprintf(stdout, "There has been an error setting the vertex 2\n");
        return 1;
    }

    /* Prints the vertex_1 and vertex_2.*/
    if (vertex_print(stdout, (void *)vertex_1) == -1 || vertex_print(stdout, (void *)vertex_2) == -1) /* Control error*/
    {
        /* Free the allocated memory in case of error.*/
        vertex_free((void *)vertex_1);
        vertex_free((void *)vertex_2);

        fprintf(stdout, "There has been an error printting the vertices\n");
        return 1;
    }

    fprintf(stdout, "\n");

    /* Compares both vertex.*/
    fprintf(stdout, "Equals? ");
    if (!vertex_cmp((void *)vertex_1, (void *)vertex_2))
    {
        /* Equals.*/
        fprintf(stdout, "Yes\n"); 
    }
    else
    {
        /* Not equals.*/
        fprintf(stdout, "No\n");
    }

    /* Prints the tag of Vertex 2.*/
    fprintf(stdout, "Vertex 2 tag: %s\n", vertex_getTag(vertex_2));

    /* Copies vertex_1 into the vertex_3.*/
    if (!(vertex_3 = vertex_copy((void *)vertex_1)))
    {
        /* Free the allocated memory in case of error.*/
        vertex_free((void *)vertex_1);
        vertex_free((void *)vertex_2);

        fprintf(stdout, "There has been an error copying the vertex 1 into the vertex 3\n");
        return 1;
    }

    /* Prints the id of vertex_3.*/
    fprintf(stdout, "Vertex 3 id: %ld\n", vertex_getId((Vertex *)vertex_3));

    /* Prints the vertex_1 and vertex_3.*/
    if (vertex_print(stdout, (void *)vertex_1) == -1 || vertex_print(stdout, vertex_3) == -1)
    {
        /* Free the allocated memory in case of error.*/
        vertex_free((void *)vertex_1);
        vertex_free((void *)vertex_2);
        vertex_free(vertex_3);

        fprintf(stdout, "There has been an error printting the vertices\n");
        return 1;
    }

    /* Compares both vertex.*/
    fprintf(stdout, "\nEquals? ");
    if (!vertex_cmp((void *)vertex_1, vertex_3))
    {
        /* Equals.*/
        fprintf(stdout, "Yes\n"); 
    }
    else
    {
        /* Not equals*/
        fprintf(stdout, "No\n"); 
    }

    /* Free all the allocated memory.*/
    vertex_free((void *)vertex_1);
    vertex_free((void *)vertex_2);
    vertex_free(vertex_3);

    return 0;
}