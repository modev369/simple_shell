#include "shell.h"

/**
 * _myexit - exits the shell
 * @myinfo: Structure containing potential arguments
 * Return: exits with a status
 * (0) if myinfo.argv[0] != "exit"
 */
int _myexit(info_t *myinfo)
{
	int exitcheck;

	if (myinfo->argv[1])
	{
		exitcheck = _erratoi(myinfo->argv[1]);
		if (exitcheck == -1)
		{
			myinfo->status = 2;
			print_error(myinfo, "Illegal number: ");
			_eputs(myinfo->argv[1]);
			_eputchar('\n');
			return (1);
		}
		myinfo->err_num = _erratoi(myinfo->argv[1]);
		return (-2);
	}
	myinfo->err_num = -1;
	return (-2);
}

/**
 * _mycd - changes the current directory of the process
 * @myinfo: Structure containing potential arguments
 * Return: Always 0
 */
int _mycd(info_t *myinfo)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!myinfo->argv[1])
	{
		dir = _getenv(myinfo, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _getenv(myinfo, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(myinfo->argv[1], "-") == 0)
	{
		if (!_getenv(myinfo, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(myinfo, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = _getenv(myinfo, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(myinfo->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(myinfo, "can't cd to ");
		_eputs(myinfo->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(myinfo, "OLDPWD", _getenv(myinfo, "PWD="));
		_setenv(myinfo, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - change current directory
 * @myinfo: Structure containing potential arguments
 * Return: Always 0
 */
int _myhelp(info_t *myinfo)
{
	char **arg_array;

	arg_array = myinfo->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
