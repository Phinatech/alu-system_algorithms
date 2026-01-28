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
 * get_parent - Gets the parent node for the next insertion
 * @root: Root of the tree
 * @index: Index where the new node will be inserted
 *
 * Return: Pointer to the parent node
 */
binary_tree_node_t *get_parent(binary_tree_node_t *root, size_t index)
{
	size_t parent_idx;
	char path[64];
	int i, depth;

	if (index == 0)
		return (NULL);

	parent_idx = (index - 1) / 2;

	if (parent_idx == 0)
		return (root);

	/* Build path in binary */
	depth = 0;
	for (i = parent_idx; i > 0; i >>= 1)
		path[depth++] = (i & 1) ? 'R' : 'L';

	/* Traverse from root following the path (in reverse) */
	for (i = depth - 2; i >= 0; i--)
	{
		if (path[i] == 'R')
			root = root->right;
		else
			root = root->left;
	}

	return (root);
}

/**
 * heapify_up - Bubbles up a node to maintain min heap property
 * @heap: Pointer to the heap
 * @node: Node to bubble up
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
 * heap_insert - Inserts a value in a Min Binary Heap
 * @heap: Pointer to the heap
 * @data: Pointer to data to store in the new node
 *
 * Return: Pointer to the created node, or NULL on failure
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *new_node, *parent;

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

	parent = get_parent(heap->root, heap->size);
	new_node->parent = parent;

	if ((heap->size & 1) == 1)
		parent->left = new_node;
	else
		parent->right = new_node;

	heap->size++;
	heapify_up(heap, new_node);

	return (new_node);
}
