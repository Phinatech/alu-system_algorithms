#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

int int_cmp(void *p1, void *p2)
{
    int *n1, *n2;
    n1 = (int *)p1;
    n2 = (int *)p2;
    return (*n1 - *n2);
}

void print_tree_structure(binary_tree_node_t *node, int depth)
{
    int i;
    if (!node) return;
    
    print_tree_structure(node->right, depth + 1);
    for (i = 0; i < depth; i++) printf("    ");
    printf("%d\n", *((int*)node->data));
    print_tree_structure(node->left, depth + 1);
}

int main(void)
{
    heap_t *heap;
    int array[] = {34, 2, 45, 23, 76};
    size_t i;

    heap = heap_create(int_cmp);
    
    for (i = 0; i < 5; i++)
    {
        printf("\n=== Inserting %d (size before: %lu) ===\n", array[i], heap->size);
        heap_insert(heap, &(array[i]));
        printf("Size after: %lu\n", heap->size);
        print_tree_structure(heap->root, 0);
    }
    
    return 0;
}
