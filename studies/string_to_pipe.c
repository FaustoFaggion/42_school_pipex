#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

//2 proccess
//1 Child proccess generate a string and sent to the parents
//2 parent is going to print the string.

int	main(void)
{
	int			pid;
	char		str[200];
	int			n;
	char		str2[200];
	int			n2;
	int			fd[2];

	if (pipe(fd) == -1)
		return (1);

	pid = fork();
	if (pid < 0)
		return (2);

	if (pid == 0)
	{
		close(fd[0]);
		printf("input string: ");
		fgets(str, 200, stdin);
		str[strlen(str) - 1] = '\0';
		n = strlen(str) + 1;

		if (write(fd[1], &n, sizeof(int)) < 0)
			return (3);
		printf("n after write: %d\n", n);
		if (write(fd[1], str, sizeof(char) * n) < 0)
			return (4);
		close(fd[1]);
	}
	else // parent
	{
		close(fd[1]);
		if (read(fd[0], &n2, sizeof(int)) < 0)
			return (5);
		printf("n2: %d\n", n2);
		if(read(fd[0], str2, sizeof(char) * n2) < 0)
			return (6);
		printf("str2: %s\n", str2);
		close(fd[0]);
		wait(NULL);
	}
}




/*
int	main(void)
{
	int			pid;
	char		str[200];
	int			n;
	char		str2[200];
	int			n2;
	int			fd[2];

	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid < 0)
		return (2);

	if (pid == 0) // child
	{
		close(fd[0]);
		printf("input string: ");
		fgets(str, 200, stdin); // want to read the str from stdin(keyboard)
		str[strlen(str) - 1] = '\0';
		n = strlen(str) + 1;
		if (write(fd[1], &n, sizeof(int)) < 0);
			return (2);
		printf("Sending n: %d\n", n);
		if (write(fd[1], str, sizeof(char) * n) < 0)
			return (3);
		printf("Sending str: %s\n", str);
		close(fd[1]);
	}
	else //parent
	{
		wait(NULL);
		close(fd[1]);
		if (read(fd[0], &n2, sizeof(int)) < 0)
			return (5);
		printf("received n: %d\n", n2);
		if (read(fd[0], str2, sizeof(char) * n2) < 0)
			return (6);
		printf("readed string: %s\n", str2);
		close(fd[0]);
	}
	return (0);
}
*/