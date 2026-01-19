#ifndef GRAPHS_H
#define GRAPHS_H

#include <stddef.h>

/**
 * struct vertex_s - Vertex of a graph
 * @index: Index of the vertex
 * @content: Content stored in the vertex
 * @nb_edges: Number of edges
 * @edges: Pointer to edges
 */
typedef struct vertex_s
{
	size_t index;
	char *content;
	size_t nb_edges;
	struct edge_s **edges;
} vertex_t;

/**
 * struct edge_s - Edge of a graph
 * @dest: Pointer to destination vertex
 * @next: Pointer to next edge
 */
typedef struct edge_s
{
	vertex_t *dest;
	struct edge_s *next;
} edge_t;

/**
 * struct graph_s - Graph structure
 * @nb_vertices: Number of vertices
 * @vertices: Array of pointers to vertices
 */
typedef struct graph_s
{
	size_t nb_vertices;
	vertex_t **vertices;
} graph_t;

/* Function prototypes */
graph_t *graph_create(void);

#endif /* GRAPHS_H */
