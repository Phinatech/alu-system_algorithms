#include "huffman.h"
#include "heap.h"
#include <stdlib.h>

/**
 * create_parent_node - Creates a parent node from two child nodes
 * @node1: First child node  
 * @node2: Second child node
 *
 * Return: Pointer to parent node, or NULL on failure
 */
binary_tree_node_t *create_parent_node(binary_tree_node_t *node1,
		binary_tree_node_t *node2)
{
	binary_tree_node_t *parent;
	symbol_t *sym1, *sym2, *parent_sym;

	sym1 = (symbol_t *)(node1->data);
	sym2 = (symbol_t *)(node2->data);

	parent_sym = symbol_create(-1, sym1->freq + sym2->freq);
	if (!parent_sym)
		return (NULL);

	parent = binary_tree_node(NULL, parent_sym);
	if (!parent)
	{
		free(parent_sym);
		return (NULL);
	}

	parent->left = node1;
	parent->right = node2;
	node1->parent = parent;
	node2->parent = parent;

	return (parent);
}

/**
 * huffman_extract_and_insert - Extracts two nodes and inserts a new one
 * @priority_queue: Pointer to the priority queue
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *node1, *node2, *parent;

	if (!priority_queue || priority_queue->size < 2)
		return (0);

	node1 = heap_extract(priority_queue);
	if (!node1)
		return (0);

	node2 = heap_extract(priority_queue);
	if (!node2)
		return (0);

	parent = create_parent_node(node1, node2);
	if (!parent)
		return (0);

	if (!heap_insert(priority_queue, parent))
	{
		parent->left = NULL;
		parent->right = NULL;
		free(parent->data);
		free(parent);
		return (0);
	}

	return (1);
}
