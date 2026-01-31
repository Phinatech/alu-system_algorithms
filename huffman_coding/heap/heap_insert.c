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
 * find_insertion_point - Find where to insert next node
 * @root: Root of the heap
 * @size: Current size of heap
 *
 * Return: Parent node where new node should be inserted
 */
binary_tree_node_t *find_insertion_point(binary_tree_node_t *root, size_t size)
{
	size_t path = size + 1;
	size_t mask = 1;
	binary_tree_node_t *node = root;

	/* Find the highest bit */
	while (mask <= path)
		mask <<= 1;
	mask >>= 2; /* Move to second highest bit */

	/* Follow the path to parent of insertion point */
	while (mask > 1)
	{
		if (path & mask)
			node = node->right;
		else
			node = node->left;
		mask >>= 1;
	}

	return (node);
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
	size_t path;

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

	parent = find_insertion_point(heap->root, heap->size);
	new->parent = parent;

	path = heap->size + 1;
	if (path & 1)
		parent->left = new;
	else
		parent->right = new;

	heap->size++;
	heapify_up(heap, new);

	return (new);
}
