#include "huffman.h"
#include "heap.h"
#include <stdlib.h>

/**
 * symbol_cmp - Compares two symbols based on their frequency
 * @p1: First pointer (binary_tree_node_t containing symbol_t)
 * @p2: Second pointer (binary_tree_node_t containing symbol_t)
 *
 * Return: Difference between frequencies
 */
int symbol_cmp(void *p1, void *p2)
{
	binary_tree_node_t *node1, *node2;
	symbol_t *sym1, *sym2;

	node1 = (binary_tree_node_t *)p1;
	node2 = (binary_tree_node_t *)p2;

	sym1 = (symbol_t *)node1->data;
	sym2 = (symbol_t *)node2->data;

	return (sym1->freq - sym2->freq);
}

/**
 * huffman_priority_queue - Creates a priority queue for Huffman coding
 * @data: Array of characters
 * @freq: Array of associated frequencies
 * @size: Size of the arrays
 *
 * Return: Pointer to the created min heap, or NULL on failure
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *heap;
	symbol_t *symbol;
	binary_tree_node_t *node;
	size_t i;

	if (!data || !freq || size == 0)
		return (NULL);

	heap = heap_create(symbol_cmp);
	if (!heap)
		return (NULL);

	for (i = 0; i < size; i++)
	{
		symbol = symbol_create(data[i], freq[i]);
		if (!symbol)
		{
			heap_delete(heap, free);
			return (NULL);
		}

		node = binary_tree_node(NULL, symbol);
		if (!node)
		{
			free(symbol);
			heap_delete(heap, free);
			return (NULL);
		}

		if (!heap_insert(heap, node))
		{
			free(node);
			free(symbol);
			heap_delete(heap, free);
			return (NULL);
		}
	}

	return (heap);
}
