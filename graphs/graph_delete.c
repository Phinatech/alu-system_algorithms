#include "graphs.h"
#include <stdlib.h>

/**
 * graph_delete - Deallocates a graph
 * @graph: Pointer to the graph to delete
 */
void graph_delete(graph_t *graph)
{
    size_t i, j;
    vertex_t *v;
    edge_t *e, *temp;
    if (!graph)
        return;
    for (i = 0; i < graph->nb_vertices; i++)
    {
        v = graph->vertices[i];
        for (j = 0; j < v->nb_edges; j++)
        {
            e = v->edges[j];
            while (e)
            {
                temp = e->next;
                free(e);
                e = temp;
            }
        }
        free(v->edges);
        free(v->content);
        free(v);
    }
    free(graph->vertices);
    free(graph);
}
