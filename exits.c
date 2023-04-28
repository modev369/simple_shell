#include "shell.h"


/**
 **_strncpy - copies a string
 *@strdest: string to be copied to
 *@strsrc: source string
 *@ncopy: number of characters to be copied
 *Return: concatenated string
 */

char *_strncpy(char *strdest, char *strsrc, int ncopy)
{
	int i, j;
	char *s = strdest;

	i = 0;
	while (strsrc[i] != '\0' && i < ncopy - 1)
	{
		strdest[i] = strsrc[i];
		i++;
	}
	if (i < ncopy)
	{
		j = i;
		while (j < ncopy)
		{
			strdest[j] = '\0';
			j++;
		}
	}
	return (s);
}



/**
 **_strncat - concatenates two strings
 *@strdest: first string
 *@strsrc: second string
 *@ncopy: amount of bytes to be maximally used
 *Return: concatenated string
 */

char *_strncat(char *strdest, char *strsrc, int ncopy)
{
	int i, j;
	char *s = strdest;

	i = 0;
	j = 0;
	while (strdest[i] != '\0')
		i++;
	while (strsrc[j] != '\0' && j < ncopy)
	{
		strdest[i] = strsrc[j];
		i++;
		j++;
	}
	if (j < ncopy)
		strdest[i] = '\0';
	return (s);
}



/**
 **_strchr - locate character in string
 *@f: string to be parsed
 *@ch: character to look for
 *Return: (f) a pointer to the memory area f
 */

char *_strchr(char *f, char ch)
{
	do {
		if (*f == ch)
			return (f);
	} while (*f++ != '\0');

	return (NULL);
}
