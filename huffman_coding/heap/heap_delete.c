#include "heap.h"
#include <stdlib.h>

/**
 * free_tree - Recursively frees all nodes in a binary tree
 * @node: Pointer to the current node
 * @free_data: Function to free the data, or NULL
 */
void free_tree(binary_tree_node_t *node, void (*free_data)(void *))
{
	if (!node)
		return;

	free_tree(node->left, free_data);
	free_tree(node->right, free_data);

	if (free_data)
		free_data(node->data);

	free(node);
}

/**
 * heap_delete - Deallocates a heap
 * @heap: Pointer to the heap to delete
 * @free_data: Function to free the content of a node
 */
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (!heap)
		return;

	free_tree(heap->root, free_data);
	free(heap);
}
