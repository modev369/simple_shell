#include "shell.h"

/**
 * hsh - main shell loop
 * @myinfo: the parameter & return info struct
 * @avect: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */

int hsh(info_t *myinfo, char **avect)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(myinfo);
		if (interactive(myinfo))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(myinfo);
		if (r != -1)
		{
			set_info(myinfo, avect);
			builtin_ret = find_builtin(myinfo);
			if (builtin_ret == -1)
				find_cmd(myinfo);
		}
		else if (interactive(myinfo))
			_putchar('\n');
		free_info(myinfo, 0);
	}
	write_history(myinfo);
	free_info(myinfo, 1);
	if (!interactive(myinfo) && myinfo->status)
		exit(myinfo->status);
	if (builtin_ret == -2)
	{
		if (myinfo->err_num == -1)
			exit(myinfo->status);
		exit(myinfo->err_num);
	}
	return (builtin_ret);
}



/**
 * find_builtin - find  builtin command
 * @myinfo: the parameter struct
 *
 * Return: -1 if builtin not found,
 *	0 if builtin executed successfully,
 *	1 if builtin found but not successful,
 *	2 if builtin signals exit()
 */
int find_builtin(info_t *myinfo)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(myinfo->argv[0], builtintbl[i].type) == 0)
		{
			myinfo->line_count++;
			built_in_ret = builtintbl[i].func(myinfo);
			break;
		}
	return (built_in_ret);
}



/**
 * find_cmd - finds a command in PATH
 * @myinfo: the parameter struct
 *
 * Return: void
 */


void find_cmd(info_t *myinfo)
{
	char *path = NULL;
	int i, k;

	myinfo->path = myinfo->argv[0];
	if (myinfo->linecount_flag == 1)
	{
		myinfo->line_count++;
		myinfo->linecount_flag = 0;
	}
	for (i = 0, k = 0; myinfo->arg[i]; i++)
		if (!is_delim(myinfo->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(myinfo, _getenv(myinfo, "PATH="), myinfo->argv[0]);
	if (path)
	{
		myinfo->path = path;
		fork_cmd(myinfo);
	}
	else
	{
		if ((interactive(myinfo) || _getenv(myinfo, "PATH=")
					|| myinfo->argv[0][0] == '/') && is_cmd(myinfo, myinfo->argv[0]))
			fork_cmd(myinfo);
		else if (*(myinfo->arg) != '\n')
		{
			myinfo->status = 127;
			print_error(myinfo, "not found\n");
		}
	}
}



/**
 * fork_cmd - fork exec thread to run cmd
 * @strinfo: parameter struct
 *
 * Return: void
 */


void fork_cmd(info_t *strinfo)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(strinfo->path, strinfo->argv, get_environ(strinfo)) == -1)
		{
			free_info(strinfo, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(strinfo->status));
		if (WIFEXITED(strinfo->status))
		{
			strinfo->status = WEXITSTATUS(strinfo->status);
			if (strinfo->status == 126)
				print_error(strinfo, "Permission denied\n");
		}
	}
}
