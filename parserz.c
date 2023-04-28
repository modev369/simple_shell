#include "shell.h"

/**
 * is_cmd - check file is an executable command or not
 * @myinfo: the info struct
 * @pathf: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */


int is_cmd(info_t *myinfo, char *pathf)
{
	struct stat st;

	(void)myinfo;
	if (!pathf || stat(pathf, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}



/**
 * dup_chars - duplicates characters
 * @strpath: the path string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */


char *dup_chars(char *strpath, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (strpath[i] != ':')
			buf[k++] = strpath[i];
	buf[k] = 0;
	return (buf);
}



/**
 * find_path - find cmd in path
 * @myinfo: the info struct
 * @pathstr: the path string
 * @cmdfind: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */


char *find_path(info_t *myinfo, char *pathstr, char *cmdfind)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmdfind) > 2) && starts_with(cmdfind, "./"))
	{
		if (is_cmd(myinfo, cmdfind))
			return (cmdfind);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmdfind);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmdfind);
			}
			if (is_cmd(myinfo, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
