#include "shell.h"



/**
 * _memset - fills memory with a constant byte
 * @area:  pointer to memory area
 * @bfill: the byte to fill *area with
 * @n: the amount of bytes to be filled
 * Return: (area) a pointer to the memory area area
 */


char *_memset(char *area, char bfill, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		area[i] = bfill;
	return (area);
}



/**
 * ffree - frees a string of strings
 * @pstr: string of strings
 */


void ffree(char **pstr)
{
	char **a = pstr;

	if (!pstr)
		return;
	while (*pstr)
		free(*pstr++);
	free(a);
}



/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc block
 * @old_s: byte size of previous block
 * @new_s: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */


void *_realloc(void *ptr, unsigned int old_s, unsigned int new_s)
{
	char *p;

	if (!ptr)
		return (malloc(new_s));
	if (!new_s)
		return (free(ptr), NULL);
	if (new_s == old_s)
		return (ptr);

	p = malloc(new_s);
	if (!p)
		return (NULL);

	old_s = old_s < new_s ? old_s : new_s;
	while (old_s--)
		p[old_s] = ((char *)ptr)[old_s];
	free(ptr);
	return (p);
}
