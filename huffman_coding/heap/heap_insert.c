#include "heap.h"
#include <stdlib.h>

/**
 * binary_tree_node - Creates a binary tree node
 * @parent: Pointer to the parent node
 * @data: Data to store in the node
 *
 * Return: Pointer to the new node, or NULL on failure
 */
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data);

/**
 * swap_data - Swaps data between two nodes
 * @a: First node
 * @b: Second node
 */
void swap_data(binary_tree_node_t *a, binary_tree_node_t *b)
{
	void *tmp = a->data;

	a->data = b->data;
	b->data = tmp;
}

/**
 * heapify_up - Restores min heap property
 * @heap: Pointer to heap
 * @node: Node to heapify
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
 * get_node - Get node at index in level order
 * @root: Root of tree
 * @index: Index to find
 *
 * Return: Node at index
 */
binary_tree_node_t *get_node(binary_tree_node_t *root, size_t index)
{
	size_t mask = 1;

	if (index == 0)
		return (root);

	while (mask <= index)
		mask <<= 1;
	mask >>= 2;

	while (mask)
	{
		root = (index & mask) ? root->right : root->left;
		mask >>= 1;
	}

	return (root);
}

/**
 * heap_insert - Inserts value in Min Binary Heap
 * @heap: Pointer to heap
 * @data: Data to insert
 *
 * Return: Pointer to created node, or NULL on failure
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *new, *parent;

	if (!heap || !data)
		return (NULL);

	new = binary_tree_node(NULL, data);
	if (!new)
		return (NULL);

	if (heap->size == 0)
	{
		heap->root = new;
		heap->size = 1;
		return (new);
	}

	parent = get_node(heap->root, (heap->size - 1) / 2);
	new->parent = parent;

	if (heap->size % 2 == 1)
		parent->left = new;
	else
		parent->right = new;

	heap->size++;
	heapify_up(heap, new);

	return (new);
}
