#include "shell.h"

/**
 * main - entry point
 * @argcount: arg count
 * @argvector: arg vector
 *
 * Return: 0 on success, 1 on error
 */


int main(int argcount, char **argvector)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));


	if (argcount == 2)
	{
		fd = open(argvector[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(argvector[0]);
				_eputs(": 0: Can't open ");
				_eputs(argvector[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, argvector);
	return (EXIT_SUCCESS);
}
