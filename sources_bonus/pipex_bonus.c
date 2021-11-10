#include "pipex.h"
#include <stdio.h>
/*
int	create_pipe(int fd[])
{
	if (pipe(fd) == -1)
		return (1);
	return(0);
}

int	create_fork()
{
	int pid;

	pid =  fork();
	if (pid < 0)
		return (2);
	return (pid);
}
*/
char	child(char *argv[], int fd[], int x)
{
	int			file;
	char		*exec_arg1;
	char		**exec_arg2;

	exec_arg2 = ft_split(argv[x + 2], ' ');
	exec_arg1 = ft_strjoin("/usr/bin/", exec_arg2[0]);
	printf("%s\n", exec_arg1);
	close(fd[0]);
	if (x == 0)
	{
		file = open(argv[x + 1], O_RDONLY);
		dup2(file, STDIN_FILENO);
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (execve(exec_arg1, exec_arg2, NULL) < 0)
		return (5);
	return (0);
}

void	parent(int fd[], int argc, int x, char	*argv[])
{
	int		n;
	char	str[200];
	int		file;

	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	if (x == argc - 4)
	{
		read(fd[0], str, 200);
		file = open(argv[argc - 1], O_WRONLY);
		n = ft_strlen(str);
		write(file, str, n);
	}
	close(fd[0]);
	x++;
}

// ./pipex file1.txt "grep Este" "cat" "wc" file2.txt (Atualizar Makefile)
int	main(int argc, char *argv[])
{
	int			fd[2];
	int			pid;
	int			x;

	x = 0;
	while (x < argc - 3)
	{
		if (pipe(fd) == -1)
			return (1);
		pid = fork();
		if (pid < 0)
			return (2);
		if (pid == 0)
			child(argv, fd, x);
		waitpid(pid, NULL, 0);
		parent(fd, argc, x, argv);
		x++;
	}
	return (0);
}
