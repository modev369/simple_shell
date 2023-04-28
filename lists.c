#include "shell.h"


/**
 * add_node - add node to start of list
 * @headnode: pointer address to head node
 * @str: field of node
 * @num: node index used by history
 *
 * Return: size of list
 */

list_t *add_node(list_t **headnode, const char *str, int num)
{
	list_t *new_head;

	if (!headnode)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *headnode;
	*headnode = new_head;
	return (new_head);
}



/**
 * add_node_end - adds a node to the end of the list
 * @headnode: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */

list_t *add_node_end(list_t **headnode, const char *str, int num)
{
	list_t *new_node, *node;

	if (!headnode)
		return (NULL);

	node = *headnode;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*headnode = new_node;
	return (new_node);
}



/**
 * print_list_str - prints only the str element
 * @ptrnode: pointer to first node
 *
 * Return: size of list
 */


size_t print_list_str(const list_t *ptrnode)
{
	size_t k = 0;

	while (ptrnode)
	{
		_puts(ptrnode->str ? ptrnode->str : "(nil)");
		_puts("\n");
		ptrnode = ptrnode->next;
		k++;
	}
	return (k);
}

/**
 * delete_node_at_index - deletes node
 * @headn: pointer to first node address
 * @indx: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */


int delete_node_at_index(list_t **headn, unsigned int indx)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!headn || !*headn)
		return (0);

	if (!indx)
	{
		node = *headn;
		*headn = (*headn)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *headn;
	while (node)
	{
		if (i == indx)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}



/**
 * free_list - frees nodes of a list
 * @headn: address of pointer to head node
 *
 * Return: void
 */

void free_list(list_t **headn)
{
	list_t *node, *next_node, *head;

	if (!headn || !*headn)
		return;
	head = *headn;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*headn = NULL;
}
