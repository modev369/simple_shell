#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */


char *_strcpy(char *dest, char *src)
{
	int h = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[h])
	{
		dest[h] = src[h];
		h++;
	}
	dest[h] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */

char *_strdup(const char *str)
{
	int len = 0;
	char *r;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	r = malloc(sizeof(char) * (len + 1));
	if (!r)
		return (NULL);
	for (len++; len--;)
		r[len] = *--str;
	return (r);
}


/**
 * _puts - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */

void _puts(char *str)
{
	int h = 0;

	if (!str)
		return;
	while (str[h] != '\0')
	{
		_putchar(str[h]);
		h++;
	}
}


/**
 * _putchar - writes the character c to stdout
 * @a: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _putchar(char a)
{
	static int h;
	static char buf[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || h >= WRITE_BUF_SIZE)
	{
		write(1, buf, h);
		h = 0;
	}
	if (a != BUF_FLUSH)
		buf[h++] = a;
	return (1);
}
