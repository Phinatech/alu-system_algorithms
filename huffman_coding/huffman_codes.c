#include "huffman.h"
#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * print_codes - Recursively prints Huffman codes for each symbol
 * @node: Current node in the tree
 * @code: Current code string
 * @depth: Current depth in the code
 */
void print_codes(binary_tree_node_t *node, char *code, int depth)
{
	symbol_t *symbol;

	if (!node)
		return;

	symbol = (symbol_t *)node->data;

	if (!node->left && !node->right)
	{
		code[depth] = '\0';
		printf("%c: %s\n", symbol->data, code);
		return;
	}

	if (node->left)
	{
		code[depth] = '0';
		print_codes(node->left, code, depth + 1);
	}

	if (node->right)
	{
		code[depth] = '1';
		print_codes(node->right, code, depth + 1);
	}
}

/**
 * free_huffman_tree - Frees the Huffman tree
 * @node: Root node of the tree
 */
void free_huffman_tree(binary_tree_node_t *node)
{
	if (!node)
		return;

	free_huffman_tree(node->left);
	free_huffman_tree(node->right);
	free(node->data);
	free(node);
}

/**
 * huffman_codes - Builds Huffman tree and prints codes
 * @data: Array of characters
 * @freq: Array of associated frequencies
 * @size: Size of the arrays
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *root;
	char code[256];

	if (!data || !freq || size == 0)
		return (0);

	root = huffman_tree(data, freq, size);
	if (!root)
		return (0);

	print_codes(root, code, 0);
	free_huffman_tree(root);

	return (1);
}
