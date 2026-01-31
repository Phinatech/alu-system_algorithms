#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stddef.h>

/* Forward declaration */
typedef struct heap_s heap_t;

/**
 * struct symbol_s - Symbol structure
 * @data: The character stored
 * @freq: The frequency of the character
 */
typedef struct symbol_s
{
	char data;
	size_t freq;
} symbol_t;

/* Function prototypes */
symbol_t *symbol_create(char data, size_t freq);
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size);

#endif /* HUFFMAN_H */
