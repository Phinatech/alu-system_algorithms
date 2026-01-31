#include "huffman.h"
#include <stdlib.h>

/**
 * symbol_create - Creates a symbol_t data structure
 * @data: Data to be stored in the structure
 * @freq: Associated frequency
 *
 * Return: Pointer to the created structure, or NULL on failure
 */
symbol_t *symbol_create(char data, size_t freq)
{
	symbol_t *symbol;

	symbol = malloc(sizeof(symbol_t));
	if (symbol == NULL)
		return (NULL);

	symbol->data = data;
	symbol->freq = freq;

	return (symbol);
}
