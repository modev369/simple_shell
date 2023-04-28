#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buf: the char buffer
 * @paddress: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *paddress)
{
	size_t j = *paddress;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*paddress = j;
	return (1);
}

/**
 * check_chain - check chaining based on last status
 * @info: parameter struct
 * @buf: char buffer
 * @paddress: address position in buf
 * @stbuf: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *paddress, size_t stbuf, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[stbuf] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[stbuf] = 0;
			j = len;
		}
	}

	*paddress = j;
}

/**
 * replace_alias - changes aliases in tokenized string
 * @info: parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *pad;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		pad = _strchr(node->str, '=');
		if (!pad)
			return (0);
		pad = _strdup(pad + 1);
		if (!pad)
			return (0);
		info->argv[0] = pad;
	}
	return (1);
}

/**
 * replace_vars - change vars in the tokenized string
 * @myinfo: parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *myinfo)
{
	int i = 0;
	list_t *node;

	for (i = 0; myinfo->argv[i]; i++)
	{
		if (myinfo->argv[i][0] != '$' || !myinfo->argv[i][1])
			continue;

		if (!_strcmp(myinfo->argv[i], "$?"))
		{
			replace_string(&(myinfo->argv[i]),
					_strdup(convert_number(myinfo->status, 10, 0)));
			continue;
		}
		if (!_strcmp(myinfo->argv[i], "$$"))
		{
			replace_string(&(myinfo->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(myinfo->env, &myinfo->argv[i][1], '=');
		if (node)
		{
			replace_string(&(myinfo->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&myinfo->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old_st: old string's address
 * @new_st: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */

int replace_string(char **old_st, char *new_st)
{
	free(*old_st);
	*old_st = new_st;
	return (1);
}
