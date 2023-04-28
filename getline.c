#include "shell.h"


/**
 * input_buf - buffers commands
 * @myinfo: parameter struct
 * @bufx: buffer address
 * @lenx: len var address
 *
 * Return: bytes read
 */

ssize_t input_buf(info_t *myinfo, char **bufx, size_t *lenx)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*lenx)
	{
		free(*bufx);
		*bufx = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(bufx, &len_p, stdin);
#else
		r = _getline(myinfo, bufx, &len_p);
#endif
		if (r > 0)
		{
			if ((*bufx)[r - 1] == '\n')
			{
				(*bufx)[r - 1] = '\0';
				r--;
			}
			myinfo->linecount_flag = 1;
			remove_comments(*bufx);
			build_history_list(myinfo, *bufx, myinfo->histcount++);
			{
				*lenx = r;
				myinfo->cmd_buf = bufx;
			}
		}
	}
	return (r);
}



/**
 * get_input - line minus newline
 * @myinfo: parameter struct
 *
 * Return: bytes read
 */

ssize_t get_input(info_t *myinfo)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(myinfo->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(myinfo, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(myinfo, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(myinfo, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			myinfo->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}


/**
 * read_buf - reads a buffer
 * @myinfo: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: x
 */


ssize_t read_buf(info_t *myinfo, char *buf, size_t *i)
{
	ssize_t x = 0;

	if (*i)
		return (0);
	x = read(myinfo->readfd, buf, READ_BUF_SIZE);
	if (x >= 0)
		*i = x;
	return (x);
}



/**
 * _getline - get next line from STDIN
 * @xinfo: parameter struct
 * @pointer: address of pointer to buffer
 * @length: size of preallocated pointer buffer if not NULL
 *
 * Return: s
 */

int _getline(info_t *xinfo, char **pointer, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *pointer;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(xinfo, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*pointer = p;
	return (s);
}



/**
 * sigintHandler - blocks ctrl-C
 * @signal_num: signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int signal_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
