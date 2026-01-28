#include "heap.h"
#include <stdlib.h>

/**
 * swap_data - Swaps data between two nodes
 * @node1: First node
 * @node2: Second node
 */
void swap_data(binary_tree_node_t *node1, binary_tree_node_t *node2)
{
	void *temp;

	temp = node1->data;
	node1->data = node2->data;
	node2->data = temp;
}

/**
 * heapify_up - Maintains min heap property by moving node up
 * @heap: Pointer to the heap
 * @node: Node to heapify up
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
 * get_parent_node - Gets the parent node for insertion at given index
 * @root: Root of the tree
 * @index: Index where new node will be inserted
 * @size: Current size of heap
 *
 * Return: Pointer to parent node
 */
binary_tree_node_t *get_parent_node(binary_tree_node_t *root, size_t index,
		size_t size)
{
	size_t parent_idx;

	if (index == 0)
		return (NULL);

	parent_idx = (index - 1) / 2;

	if (parent_idx == 0)
		return (root);

	if (index < size / 2)
		return (get_parent_node(root->left, index - (parent_idx + 1), size / 2));
	else
		return (get_parent_node(root->right, index - (size / 2 + parent_idx),
					size - size / 2));
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

	if (heap == NULL || data == NULL)
		return (NULL);

	if (heap->root == NULL)
	{
		new_node = binary_tree_node(NULL, data);
		if (new_node == NULL)
			return (NULL);
		heap->root = new_node;
		heap->size++;
		return (new_node);
	}

	parent = get_parent_node(heap->root, heap->size, heap->size);
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
