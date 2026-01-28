#include "heap.h"
#include <stdlib.h>

/**
 * heapify_up - Maintains min heap property by moving node up
 * @heap: Pointer to the heap
 * @node: Node to heapify up
 */
void heapify_up(heap_t *heap, binary_tree_node_t *node)
{
	void *temp;

	while (node->parent && heap->data_cmp(node->data, node->parent->data) < 0)
	{
		temp = node->data;
		node->data = node->parent->data;
		node->parent->data = temp;
		node = node->parent;
	}
}

/**
 * get_node_at_index - Gets node at specific index using level-order
 * @root: Root of the tree
 * @index: Index of the node to find
 *
 * Return: Pointer to the node at index
 */
binary_tree_node_t *get_node_at_index(binary_tree_node_t *root, size_t index)
{
	size_t mask, bit_position;

	if (index == 0)
		return (root);

	/* Find the highest bit position */
	for (mask = index, bit_position = 0; mask > 1; mask >>= 1, bit_position++)
		;

	/* Start from the second-highest bit */
	if (bit_position > 0)
		mask = 1 << (bit_position - 1);
	else
		mask = 0;

	/* Traverse the tree following the bits */
	while (mask > 0)
	{
		if (index & mask)
			root = root->right;
		else
			root = root->left;
		mask >>= 1;
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

	if (heap == NULL || data == NULL)
		return (NULL);

	if (heap->root == NULL)
	{
		new_node = binary_tree_node(NULL, data);
		if (new_node == NULL)
			return (NULL);
		heap->root = new_node;
		heap->size = 1;
		return (new_node);
	}

	parent_index = (heap->size - 1) / 2;
	parent = get_node_at_index(heap->root, parent_index);
	
	new_node = binary_tree_node(parent, data);
	if (new_node == NULL)
		return (NULL);

	if (heap->size % 2 == 1)
		parent->left = new_node;
	else
		parent->right = new_node;

	heap->size++;
	heapify_up(heap, new_node);

	return (new_node);
}
