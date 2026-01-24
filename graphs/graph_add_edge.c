#include "graphs.h"
#include <stdlib.h>
#include <string.h>

/**
 * add_edge_to_vertex - Helper function to add an edge to a vertex
 * @src: Source vertex
 * @dest: Destination vertex
 *
 * Return: 1 on success, 0 on failure
 */
static int add_edge_to_vertex(vertex_t *src, vertex_t *dest)
{
	edge_t *new_edge;
	edge_t *edge;

	/* Check if edge already exists */
	edge = src->edges;
	while (edge)
	{
		if (edge->dest == dest)
			return (1);
		edge = edge->next;
	}

	/* Create new edge */
	new_edge = malloc(sizeof(edge_t));
	if (!new_edge)
		return (0);

	new_edge->dest = dest;
	new_edge->next = src->edges;
	src->edges = new_edge;
	src->nb_edges++;

	return (1);
}

/**
 * graph_add_edge - Adds an edge between two vertices
 * @graph: Pointer to the graph
 * @src: String identifying the source vertex
 * @dest: String identifying the destination vertex
 * @type: Type of edge (UNIDIRECTIONAL or BIDIRECTIONAL)
 *
 * Return: 1 on success, 0 on failure
 */
int graph_add_edge(graph_t *graph, const char *src, const char *dest,
		   edge_type_t type)
{
	vertex_t *src_vertex = NULL, *dest_vertex = NULL;
	size_t i;

	if (!graph || !src || !dest)
		return (0);

	/* Find source and destination vertices */
	vertex_t *v = graph->vertices;
	for (i = 0; i < graph->nb_vertices && v; i++, v = v->next)
	{
		if (strcmp(v->content, src) == 0)
			src_vertex = v;
		if (strcmp(v->content, dest) == 0)
			dest_vertex = v;
	}

	/* Both vertices must exist */
	if (!src_vertex || !dest_vertex)
		return (0);

	/* Add edge from src to dest */
	if (!add_edge_to_vertex(src_vertex, dest_vertex))
		return (0);

	/* If bidirectional, add edge from dest to src */
	if (type == BIDIRECTIONAL)
	{
		if (!add_edge_to_vertex(dest_vertex, src_vertex))
			return (0);
	}

	return (1);
}
