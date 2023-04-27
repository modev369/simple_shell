#include "shell.h"

/**
 * _erratoi - convert string to int
 * @mystring: string to convert
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */


int _erratoi(char *mystring)
{
	int i = 0;
	unsigned long int results = 0;

	if (*mystring == '+')
		mystring++;
	for (i = 0;  mystring[i] != '\0'; i++)
	{
		if (mystring[i] >= '0' && mystring[i] <= '9')
		{
			results *= 10;
			results += (mystring[i] - '0');
			if (results > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (results);
}



/**
 * print_error - print error message
 * @myinfo: parameter struct
 * @errstr: string with error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */


void print_error(info_t *myinfo, char *errstr)
{
	_eputs(myinfo->fname);
	_eputs(": ");
	print_d(myinfo->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(myinfo->argv[0]);
	_eputs(": ");
	_eputs(errstr);
}



/**
 * print_d - prints integer number
 * @xinput: the input
 * @fdes: the filedescriptor to write to
 *
 * Return: number of characters printed
 */

int print_d(int xinput, int fdes)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fdes == STDERR_FILENO)
		__putchar = _eputchar;
	if (xinput < 0)
	{
		_abs_ = -xinput;
		__putchar('-');
		count++;
	}
	else
		_abs_ = xinput;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}



/**
 * convert_number - convert number
 * @xnum: number
 * @ybase: base
 * @flags: argument flags
 *
 * Return: string
 */

char *convert_number(long int xnum, int ybase, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *pointer;
	unsigned long n = xnum;

	if (!(flags & CONVERT_UNSIGNED) && xnum < 0)
	{
		n = -xnum;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pointer = &buffer[49];
	*pointer = '\0';

	do	{
		*--pointer = array[n % ybase];
		n /= ybase;
	} while (n != 0);

	if (sign)
		*--pointer = sign;
	return (pointer);
}



/**
 * remove_comments - replace '#' with '\0'
 * @bufadd: address of the string
 *
 * Return: Always 0;
 */

void remove_comments(char *bufadd)
{
	int i;

	for (i = 0; bufadd[i] != '\0'; i++)
		if (bufadd[i] == '#' && (!i || bufadd[i - 1] == ' '))
		{
			bufadd[i] = '\0';
			break;
		}
}
