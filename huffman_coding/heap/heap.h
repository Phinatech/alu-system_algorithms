#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

/**
 * struct binary_tree_node_s - Binary tree node structure
 * @data: Data stored in the node
 * @left: Pointer to the left child
 * @right: Pointer to the right child
 * @parent: Pointer to the parent node
 */
typedef struct binary_tree_node_s
{
	void *data;
	struct binary_tree_node_s *left;
	struct binary_tree_node_s *right;
	struct binary_tree_node_s *parent;
} binary_tree_node_t;

/**
 * struct heap_s - Heap structure
 * @size: Number of nodes in the heap
 * @data_cmp: Pointer to comparison function
 * @root: Pointer to the root node of the heap
 */
typedef struct heap_s
{
	size_t size;
	int (*data_cmp)(void *, void *);
	binary_tree_node_t *root;
} heap_t;

/* Function prototypes */
heap_t *heap_create(int (*data_cmp)(void *, void *));
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data);
binary_tree_node_t *heap_insert(heap_t *heap, void *data);
void *heap_extract(heap_t *heap);
void binary_tree_print(const binary_tree_node_t *root,
	int (*print_data)(char *, void *));

#endif /* HEAP_H */
