#include "graphs.h"
#include <stdlib.h>

/**
 * graph_create - Allocates memory to store a graph_t structure
 *
 * Return: Pointer to the allocated structure, or NULL on failure
 */
graph_t *graph_create(void)
{
	graph_t *graph;

	graph = malloc(sizeof(graph_t));
	if (graph == NULL)
		return (NULL);

	graph->nb_vertices = 0;
	graph->vertices = NULL;

	return (graph);
}
