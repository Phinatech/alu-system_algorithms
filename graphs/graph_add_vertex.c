#include <stdlib.h>
#include <string.h>
#include "graphs.h"

/**
 * graph_add_vertex - adds a vertex to an existing graph
 * @graph: pointer to the graph to add the vertex to
 * @str: string to store in the new vertex
 *
 * Return: pointer to the created vertex, or NULL on failure
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *new_vertex, *last;

	if (!graph || !str)
		return (NULL);

	/* Check if vertex with same str already exists */
	last = graph->vertices;
	while (last)
	{
		if (strcmp(last->content, str) == 0)
			return (NULL);
		if (!last->next)
			break;
		last = last->next;
	}

	new_vertex = malloc(sizeof(vertex_t));
	if (!new_vertex)
		return (NULL);

	new_vertex->content = strdup(str);
	if (!new_vertex->content)
	{
		free(new_vertex);
		return (NULL);
	}

	new_vertex->index = graph->nb_vertices++;
	new_vertex->edges = NULL;
	new_vertex->next = NULL;

	if (!graph->vertices)
		graph->vertices = new_vertex;
	else
		last->next = new_vertex;

	return (new_vertex);
}
