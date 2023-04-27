#include "shell.h"

/**
 * _myenv - print current environment
 * @myinfo: Structure containing potential arguments
 * Return: Always 0
 */
int _myenv(info_t *myinfo)
{
	print_list_str(myinfo->env);
	return (0);
}

/**
 * _getenv - get value of environ var
 * @myinfo: Structure containing potential arguments. Used to maintain
 * @envname: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *myinfo, const char *envname)
{
	list_t *node = myinfo->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, envname);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - set a new environment variable
 * @myinfo: Structure containing potential arguments
 *  Return: Always 0
 */
int _mysetenv(info_t *myinfo)
{
	if (myinfo->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(myinfo, myinfo->argv[1], myinfo->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - delete an environment var
 * @myinfo: Structure containing potential arguments
 * Return: Always 0
 */
int _myunsetenv(info_t *myinfo)
{
	int i;

	if (myinfo->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= myinfo->argc; i++)
		_unsetenv(myinfo, myinfo->argv[i]);

	return (0);
}

/**
 * populate_env_list - populate the env list
 * @myinfo: Structure containing potential arguments
 * Return: Always 0
 */
int populate_env_list(info_t *myinfo)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	myinfo->env = node;
	return (0);
}
