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
	binary_tree_node_t *node1, *node2, *parent_node, *new_node;
	symbol_t *symbol1, *symbol2, *new_symbol;
	size_t combined_freq;

	if (!priority_queue || priority_queue->size < 2)
		return (0);

	node1 = heap_extract(priority_queue);
	if (!node1)
		return (0);

	node2 = heap_extract(priority_queue);
	if (!node2)
	{
		heap_insert(priority_queue, node1);
		return (0);
	}

	symbol1 = (symbol_t *)((binary_tree_node_t *)node1)->data;
	symbol2 = (symbol_t *)((binary_tree_node_t *)node2)->data;

	combined_freq = symbol1->freq + symbol2->freq;

	new_symbol = symbol_create(-1, combined_freq);
	if (!new_symbol)
	{
		heap_insert(priority_queue, node1);
		heap_insert(priority_queue, node2);
		return (0);
	}

	parent_node = binary_tree_node(NULL, new_symbol);
	if (!parent_node)
	{
		free(new_symbol);
		heap_insert(priority_queue, node1);
		heap_insert(priority_queue, node2);
		return (0);
	}

	parent_node->left = (binary_tree_node_t *)node1;
	parent_node->right = (binary_tree_node_t *)node2;
	((binary_tree_node_t *)node1)->parent = parent_node;
	((binary_tree_node_t *)node2)->parent = parent_node;

	new_node = binary_tree_node(NULL, parent_node);
	if (!new_node)
	{
		free(parent_node);
		free(new_symbol);
		heap_insert(priority_queue, node1);
		heap_insert(priority_queue, node2);
		return (0);
	}

	if (!heap_insert(priority_queue, new_node))
	{
		free(new_node);
		free(parent_node);
		free(new_symbol);
		heap_insert(priority_queue, node1);
		heap_insert(priority_queue, node2);
		return (0);
	}

	return (1);
}
