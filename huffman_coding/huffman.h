#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stddef.h>

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

#endif /* HUFFMAN_H */
