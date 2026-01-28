#include "heap.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int _print_t(const binary_tree_node_t *tree, int offset, int depth,
	char **s, int (*print_data)(char *, void *))
{
	char b[6];
	int width, left, right, is_left, i;

	if (!tree)
		return (0);
	is_left = (tree->parent && tree->parent->left == tree);
	width = print_data(b, tree->data);
	left = _print_t(tree->left, offset, depth + 1, s, print_data);
	right = _print_t(tree->right, offset + left + width, depth + 1, s, print_data);
	for (i = 0; i < width; i++)
		s[depth][offset + left + i] = b[i];
	if (depth && is_left)
	{
		for (i = 0; i < width + right; i++)
			s[depth - 1][offset + left + width / 2 + i] = '-';
		s[depth - 1][offset + left + width / 2] = '.';
	}
	else if (depth && !is_left)
	{
		for (i = 0; i < left + width; i++)
			s[depth - 1][offset - width / 2 + i] = '-';
		s[depth - 1][offset + left + width / 2] = '.';
	}
	return (left + width + right);
}

static size_t _height(const binary_tree_node_t *tree)
{
	size_t height_l, height_r;

	height_l = tree->left ? 1 + _height(tree->left) : 0;
	height_r = tree->right ? 1 + _height(tree->right) : 0;
	return (height_l > height_r ? height_l : height_r);
}

void binary_tree_print(const binary_tree_node_t *root,
	int (*print_data)(char *, void *))
{
	char **s;
	size_t height, i, j;

	if (!root)
		return;
	height = _height(root);
	s = malloc(sizeof(*s) * (height + 1));
	if (!s)
		return;
	for (i = 0; i < height + 1; i++)
	{
		s[i] = malloc(sizeof(**s) * 255);
		if (!s[i])
			return;
		memset(s[i], 32, 255);
	}
	_print_t(root, 0, 0, s, print_data);
	for (i = 0; i < height + 1; i++)
	{
		for (j = 254; j > 1; --j)
		{
			if (s[i][j] != ' ')
				break;
			s[i][j] = '\0';
		}
		printf("%s\n", s[i]);
		free(s[i]);
	}
	free(s);
}
