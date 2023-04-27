#include "shell.h"





/**
 * interactive - check if shell is interactive mode
 * @stradd: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *stradd)
{
	return (isatty(STDIN_FILENO) && stradd->readfd <= 2);
}



/**
 * is_delim - determine if character is a delimeter
 * @c: char to check
 * @delimeter: delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char a, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == a)
			return (1);
	return (0);
}



/**
 * _isalpha - check if alphabet character
 * @c: character to check
 * Return: 1 if c is alphabetic, 0 if not
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}



/**
 * _atoi - converts string to integer
 * @stconv: string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *stconv)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; stconv[i] != '\0' && flag != 2; i++)
	{
		if (stconv[i] == '-')
			sign *= -1;

		if (stconv[i] >= '0' && stconv[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (stconv[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
