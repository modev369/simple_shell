#include "shell.h"


/**
 * clear_info - initializes info_t struct
 * @myinfo: struct address
 */


void clear_info(info_t *myinfo)
{
	myinfo->arg = NULL;
	myinfo->argv = NULL;
	myinfo->path = NULL;
	myinfo->argc = 0;
}



/**
 * set_info - initializes info_t struct
 * @myinfo: struct address
 * @argumentv: argument vector
 */


void set_info(info_t *myinfo, char **argumentv)
{
	int i = 0;

	myinfo->fname = argumentv[0];
	if (myinfo->arg)
	{
		myinfo->argv = strtow(myinfo->arg, " \t");
		if (!myinfo->argv)
		{
			myinfo->argv = malloc(sizeof(char *) * 2);
			if (myinfo->argv)
			{
				myinfo->argv[0] = _strdup(myinfo->arg);
				myinfo->argv[1] = NULL;
			}
		}
		for (i = 0; myinfo->argv && myinfo->argv[i]; i++)
			;
		myinfo->argc = i;

		replace_alias(myinfo);
		replace_vars(myinfo);
	}
}


/**
 * free_info - free info_t struct
 * @myinfo: the struct address
 * @allfree: true if freeing all fields
 */


void free_info(info_t *myinfo, int allfree)
{
	ffree(myinfo->argv);
	myinfo->argv = NULL;
	myinfo->path = NULL;
	if (allfree)
	{
		if (!myinfo->cmd_buf)
			free(myinfo->arg);
		if (myinfo->env)
			free_list(&(myinfo->env));
		if (myinfo->history)
			free_list(&(myinfo->history));
		if (myinfo->alias)
			free_list(&(myinfo->alias));
		ffree(myinfo->environ);
			myinfo->environ = NULL;
		bfree((void **)myinfo->cmd_buf);
		if (myinfo->readfd > 2)
			close(myinfo->readfd);
		_putchar(BUF_FLUSH);
	}
}
