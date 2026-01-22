#include "graphs.h"
#include <stdlib.h>

/**
 * graph_delete - Deallocates a graph
 * @graph: Pointer to the graph to delete
 */
void graph_delete(graph_t *graph)
{
    size_t i;
    vertex_t *v;
    edge_t *e, *temp_e;

    if (!graph)
        return;

    for (i = 0; i < graph->nb_vertices; i++)
    {
        v = graph->vertices[i];
        if (v)
        {
            /* Free all edges in the linked list */
            e = v->edges[0];  /* First edge in the array points to linked list */
            while (e)
            {
                temp_e = e->next;
                free(e);
                e = temp_e;
            }
            
            /* Free the edges array */
            free(v->edges);
            
            /* Free the content */
            free(v->content);
            
            /* Free the vertex */
            free(v);
        }
    }
    
    /* Free the vertices array */
    free(graph->vertices);
    
    /* Free the graph */
    free(graph);
}
