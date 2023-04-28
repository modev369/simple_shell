#include "shell.h"

/**
 * bfree - frees a pointer
 * @ptrfree: address of pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **ptrfree)
{
	if (ptrfree && *ptrfree)
	{
		free(*ptrfree);
		*ptrfree = NULL;
		return (1);
	}
	return (0);
}
