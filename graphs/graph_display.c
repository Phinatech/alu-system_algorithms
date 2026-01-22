#include <stdio.h>
#include "graphs.h"

/**
 * graph_display - Displays the graph
 * @graph: Pointer to the graph to display
 */
void graph_display(const graph_t *graph)
{
    size_t i;

    if (!graph)
        return;

    printf("Number of vertices: %lu\n", graph->nb_vertices);
    for (i = 0; i < graph->nb_vertices; i++)
    {
        printf("[%lu] %s\n", graph->vertices[i].index,
               graph->vertices[i].content);
    }
}
