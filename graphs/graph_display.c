#include <stdio.h>
#include "graphs.h"

/**
 * graph_display - Displays the contents of a graph_t data structure
 * @graph: Pointer to the graph to display
 */
void graph_display(const graph_t *graph)
{
	vertex_t *vertex;
	edge_t *edge;

	if (!graph)
		return;

	vertex = graph->vertices;
	while (vertex)
	{
		printf("[%lu] %s", vertex->index, vertex->content);

		edge = vertex->edges;
		while (edge)
		{
			printf(" -> %s", edge->dest->content);
			edge = edge->next;
		}

		printf("\n");
		vertex = vertex->next;
	}
}
