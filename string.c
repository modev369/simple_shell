#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @strchk: the string to check
 *
 * Return: length of string
 */

int _strlen(char *strchk)
{
	int i = 0;

	if (!strchk)
		return (0);

	while (*strchk++)
		i++;
	return (i);
}

/**
 * _strcmp - lexicographic comparison of two strangs.
 * @st1: the first strang
 * @st2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */


int _strcmp(char *st1, char *st2)
{
	while (*st1 && *st2)
	{
		if (*st1 != *st2)
			return (*st1 - *st2);
		st1++;
		st2++;
	}
	if (*st1 == *st2)
		return (0);
	else
		return (*st1 < *st2 ? -1 : 1);
}



/**
 * starts_with - check needle if starts with haystack
 * @haystack: string to search
 * @needle: substring to find
 *
 * Return: next char of haystack address or NULL
 */


char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}



/**
 * _strcat - concatenates two strings
 * @destbuf: the destination buffer
 * @srcbuf: the source buffer
 *
 * Return: pointer to destination buffer
 */

char *_strcat(char *destbuf, char *srcbuf)
{
	char *ret = destbuf;

	while (*destbuf)
		destbuf++;
	while (*srcbuf)
		*destbuf++ = *srcbuf++;
	*destbuf = *srcbuf;
	return (ret);
}
