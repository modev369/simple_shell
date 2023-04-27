#include "shell.h"

/**
 * get_history_file - gets the history file
 * @myinfo: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *myinfo)
{
	char *buf, *dir;

	dir = _getenv(myinfo, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - creates a file
 * @myinfo: parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *myinfo)
{
	ssize_t fdescript;
	char *filename = get_history_file(myinfo);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fdescript = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fdescript == -1)
		return (-1);
	for (node = myinfo->history; node; node = node->next)
	{
		_putsfd(node->str, fdescript);
		_putfd('\n', fdescript);
	}
	_putfd(BUF_FLUSH, fdescript);
	close(fdescript);
	return (1);
}

/**
 * read_history - read history from file
 * @myinfo:  parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *myinfo)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(myinfo);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(myinfo, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(myinfo, buf + last, linecount++);
	free(buf);
	myinfo->histcount = linecount;
	while (myinfo->histcount-- >= HIST_MAX)
		delete_node_at_index(&(myinfo->history), 0);
	renumber_history(myinfo);
	return (myinfo->histcount);
}



/**
 * build_history_list - add entry to history
 * @myinfo: Structure containing potential arguments
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */


int build_history_list(info_t *myinfo, char *buf, int linecount)
{
	list_t *node = NULL;

	if (myinfo->history)
		node = myinfo->history;
	add_node_end(&node, buf, linecount);

	if (!myinfo->history)
		myinfo->history = node;

	return (0);
}

/**
 * renumber_history - renumbers history linked list
 * @myinfo: Structure containing potential arguments
 * Return: updated new histcount
 */
int renumber_history(info_t *myinfo)
{
	list_t *node = myinfo->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (myinfo->histcount = i);
}
