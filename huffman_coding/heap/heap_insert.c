#include "heap.h"
#include <stdlib.h>

/**
 * swap_data - Swaps data between two nodes
 * @a: First node
 * @b: Second node
 */
void swap_data(binary_tree_node_t *a, binary_tree_node_t *b)
{
	void *tmp;

	tmp = a->data;
	a->data = b->data;
	b->data = tmp;
}

/**
 * heapify_up - Maintains min heap property by bubbling up
 * @heap: Pointer to the heap
 * @node: Node to bubble up
 */
void heapify_up(heap_t *heap, binary_tree_node_t *node)
{
	while (node->parent && heap->data_cmp(node->data, node->parent->data) < 0)
	{
		swap_data(node, node->parent);
		node = node->parent;
	}
}

/**
 * get_node_at_index - Gets node at specified index (level-order)
 * @root: Root of the tree
 * @index: Index of the node to find
 *
 * Return: Pointer to node at index
 */
binary_tree_node_t *get_node_at_index(binary_tree_node_t *root, size_t index)
{
	size_t depth, level, path;
	int bit;

	if (index == 0)
		return (root);

	/* Calculate depth of the node */
	for (depth = 0, level = 1; level <= index; depth++)
		level = (level << 1) + 1;

	/* Get path to node (relative position in its level) */
	path = index - ((1 << depth) - 1);

	/* Traverse from root following the path */
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
 * heap_insert - Inserts a value in a Min Binary Heap
 * @heap: Pointer to the heap
 * @data: Pointer to data to store in the new node
 *
 * Return: Pointer to the created node, or NULL on failure
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *new_node, *parent;
	size_t parent_index;

	if (!heap || !data)
		return (NULL);

	new_node = binary_tree_node(NULL, data);
	if (!new_node)
		return (NULL);

	if (heap->size == 0)
	{
		heap->root = new_node;
		heap->size = 1;
		return (new_node);
	}

	parent_index = (heap->size - 1) / 2;
	parent = get_node_at_index(heap->root, parent_index);

	new_node->parent = parent;

	if (heap->size % 2 == 1)
		parent->left = new_node;
	else
		parent->right = new_node;

	heap->size++;
	heapify_up(heap, new_node);

	return (new_node);
}