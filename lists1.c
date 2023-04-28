#include "shell.h"

/**
 * list_len - get length of linked list
 * @headn: pointer first node
 *
 * Return: size of list
 */
size_t list_len(const list_t *headn)
{
	size_t i = 0;

	while (headn)
	{
		headn = headn->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - returns an array of strings
 * @headn: pointer to the first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *headn)
{
	list_t *node = headn;
	size_t i = list_len(headn), j;
	char **strs;
	char *str;

	if (!headn || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;

	return (strs);
}


/**
 * print_list - prints a list_t linked list
 * @headn: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *headn)
{
	size_t i = 0;

	while (headn)
	{
		_puts(convert_number(headn->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(headn->str ? headn->str : "(nil)");
		_puts("\n");
		headn = headn->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - returns node starts with prefix
 * @head: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *head, char *prefix, char c)
{
	char *p = NULL;

	while (head)
	{
		p = starts_with(head->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (head);
		head = head->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * @headn: pointer to list head
 * @nodex: pointer to the node
 *
 * Return: node index or -1
 */
ssize_t get_node_index(list_t *headn, list_t *nodex)
{
	size_t i = 0;

	while (headn)
	{
		if (headn == nodex)
			return (i);
		headn = headn->next;
		i++;
	}
	return (-1);
}
