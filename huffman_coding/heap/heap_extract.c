#include "heap.h"
#include <stdlib.h>

/**
 * get_last_node - Gets the last node in the heap (level-order)
 * @root: Root of the tree
 * @index: Index of the last node
 *
 * Return: Pointer to the last node
 */
binary_tree_node_t *get_last_node(binary_tree_node_t *root, size_t index)
{
	size_t depth, level, path;
	int bit;

	if (index == 0)
		return (root);

	for (depth = 0, level = 1; level <= index; depth++)
		level = (level << 1) + 1;

	path = index - ((1 << depth) - 1);

	for (bit = depth - 1; bit >= 0; bit--)
	{
		if ((path >> bit) & 1)
			root = root->right;
		else
			root = root->left;
	}

	return (root);
}

/**
 * heapify_down - Maintains min heap property by bubbling down
 * @heap: Pointer to the heap
 * @node: Node to bubble down
 */
void heapify_down(heap_t *heap, binary_tree_node_t *node)
{
	binary_tree_node_t *smallest;
	void *temp;

	while (node)
	{
		smallest = node;

		if (node->left && heap->data_cmp(node->left->data, smallest->data) < 0)
			smallest = node->left;

		if (node->right && heap->data_cmp(node->right->data, smallest->data) < 0)
			smallest = node->right;

		if (smallest == node)
			break;

		temp = node->data;
		node->data = smallest->data;
		smallest->data = temp;

		node = smallest;
	}
}

/**
 * heap_extract - Extracts the root value of a Min Binary Heap
 * @heap: Pointer to the heap
 *
 * Return: Pointer to the data from the root node, or NULL on failure
 */
void *heap_extract(heap_t *heap)
{
	void *data;
	binary_tree_node_t *last_node;

	if (!heap || !heap->root)
		return (NULL);

	data = heap->root->data;

	if (heap->size == 1)
	{
		free(heap->root);
		heap->root = NULL;
		heap->size = 0;
		return (data);
	}

	last_node = get_last_node(heap->root, heap->size - 1);

	heap->root->data = last_node->data;

	if (last_node->parent)
	{
		if (last_node->parent->left == last_node)
			last_node->parent->left = NULL;
		else
			last_node->parent->right = NULL;
	}

	free(last_node);
	heap->size--;

	heapify_down(heap, heap->root);

	return (data);
}
