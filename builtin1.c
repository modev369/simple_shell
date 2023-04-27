#include "shell.h"



/**
 * _myhistory - display history list
 * @myinfo: Structure containing potential arguments
 *  Return: Always 0
 */
int _myhistory(info_t *myinfo)
{
	print_list(myinfo->history);
	return (0);
}



/**
 * unset_alias - set alias to a string
 * @myinfo: parameter struct
 * @stralias: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */

int unset_alias(info_t *myinfo, char *stralias)
{
	char *p, c;
	int ret;

	p = _strchr(stralias, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(myinfo->alias),
	get_node_index(myinfo->alias, node_starts_with(myinfo->alias, stralias, -1)));
	*p = c;
	return (ret);
}



/**
 * set_alias - set alias to string
 * @myinfo: parameter struct
 * @stralias: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */

int set_alias(info_t *myinfo, char *stralias)
{
	char *p;

	p = _strchr(stralias, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(myinfo, stralias));

	unset_alias(myinfo, stralias);
	return (add_node_end(&(myinfo->alias), stralias, 0) == NULL);
}



/**
 * print_alias - print alias
 * @nodealias: alias node
 *
 * Return: Always 0 on success, 1 on error
 */

int print_alias(list_t *nodealias)
{
	char *p = NULL, *a = NULL;

	if (nodealias)
	{
		p = _strchr(nodealias->str, '=');
		for (a = nodealias->str; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}



/**
 * _myalias - mimics the alias builtin
 * @myinfo: Structure containing potential arguments
 *  Return: Always 0
 */

int _myalias(info_t *myinfo)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (myinfo->argc == 1)
	{
		node = myinfo->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; myinfo->argv[i]; i++)
	{
		p = _strchr(myinfo->argv[i], '=');
		if (p)
			set_alias(myinfo, myinfo->argv[i]);
		else
			print_alias(node_starts_with(myinfo->alias, myinfo->argv[i], '='));
	}

	return (0);
}
