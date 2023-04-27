#include "shell.h"


/**
 * get_environ - returns the string array of environ
 * @myinfo: Structure containing potential arguments
 * Return: Always 0
 */

char **get_environ(info_t *myinfo)
{
	if (!myinfo->environ || myinfo->env_changed)
	{
		myinfo->environ = list_to_strings(myinfo->env);
		myinfo->env_changed = 0;
	}

	return (myinfo->environ);
}


/**
 * _unsetenv - Remove environment variable
 * @myinfo: Structure containing potential arguments
 *  Return: 1 on delete, 0 otherwise
 * @envvar: the string env var property
 */

int _unsetenv(info_t *myinfo, char *envvar)
{
	list_t *node = myinfo->env;
	size_t i = 0;
	char *p;

	if (!node || !envvar)
		return (0);

	while (node)
	{
		p = starts_with(node->str, envvar);
		if (p && *p == '=')
		{
			myinfo->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = myinfo->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (myinfo->env_changed);
}


/**
 * _setenv - Initialize a new environment variable
 * @myinfo: Structure containing potential arguments
 * @envvar: the string env var property
 * @envvalue: the string env var value
 *  Return: Always 0
 */

int _setenv(info_t *myinfo, char *envvar, char *envvalue)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!envvar || !envvalue)
		return (0);

	buf = malloc(_strlen(envvar) + _strlen(envvalue) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, envvar);
	_strcat(buf, "=");
	_strcat(buf, envvalue);
	node = myinfo->env;
	
  while (node)
	{
		p = starts_with(node->str, envvar);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			myinfo->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(myinfo->env), buf, 0);
	free(buf);
	myinfo->env_changed = 1;
	return (0);
}
