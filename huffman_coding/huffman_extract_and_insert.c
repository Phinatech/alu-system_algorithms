#include "huffman.h"
#include "heap.h"
#include <stdlib.h>

/**
 * huffman_extract_and_insert - Extracts two nodes and inserts a new one
 * @priority_queue: Pointer to the priority queue
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *node1, *node2, *parent;
	symbol_t *sym1, *sym2, *parent_sym;

	if (!priority_queue || priority_queue->size < 2)
		return (0);

	node1 = heap_extract(priority_queue);
	if (!node1)
		return (0);

	node2 = heap_extract(priority_queue);
	if (!node2)
		return (0);

	sym1 = (symbol_t *)(node1->data);
	sym2 = (symbol_t *)(node2->data);

	parent_sym = symbol_create(-1, sym1->freq + sym2->freq);
	if (!parent_sym)
		return (0);

	parent = binary_tree_node(NULL, parent_sym);
	if (!parent)
	{
		free(parent_sym);
		return (0);
	}

	parent->left = node1;
	parent->right = node2;
	node1->parent = parent;
	node2->parent = parent;

	if (!heap_insert(priority_queue, parent))
	{
		parent->left = NULL;
		parent->right = NULL;
		free(parent);
		free(parent_sym);
		return (0);
	}

	return (1);
}
