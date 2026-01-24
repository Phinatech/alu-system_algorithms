
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

	if (!graph)
		return;

	for (i = 0; i < graph->nb_vertices; i++)
	{
		v = &graph->vertices[i];

		free(v->edges);
		free(v->content);
		free(v);
	}

	free(graph->vertices);
	free(graph);
}
