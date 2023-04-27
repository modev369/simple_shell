#include "shell.h"

/**
 * _eputs - print input string
 * @strprnt: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *strprnt)
{
	int i = 0;

	if (!strprnt)
		return;
	while (strprnt[i] != '\0')
	{
		_eputchar(strprnt[i]);
		i++;
	}
}

/**
 * _eputchar - writes the character a to stderr
 * @a: character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set
 */
int _eputchar(char a)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (a != BUF_FLUSH)
		buf[i++] = a;
	return (1);
}

/**
 * _putfd - writes a to given fdes
 * @a: The character to print
 * @fdes: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set
 */
int _putfd(char a, int fdes)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (a == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fdes, buf, i);
		i = 0;
	}
	if (a != BUF_FLUSH)
		buf[i++] = a;
	return (1);
}

/**
 * _putsfd - print string from input
 * @mystr: string to print
 * @fdes: the filedescriptor
 *
 * Return: the number of chars
 */
int _putsfd(char *mystr, int fdes)
{
	int i = 0;

	if (!mystr)
		return (0);
	while (*mystr)
	{
		i += _putfd(*mystr++, fdes);
	}
	return (i);
}
