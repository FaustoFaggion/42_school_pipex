#include "pipex.h"
#include <stdio.h>

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

char	child(int argc, char *argv[], int fd[], int x)
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
	if (x != argc - 4)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (execve(exec_arg1, exec_arg2, NULL) < 0)
		return (5);
	return(0);
}
// ./pipex file1.txt "grep Este" "cat" "wc" file2.txt (Atualizar Makefile)
int	main(int argc, char *argv[])
{
	int			fd[2];
	int			pid;
	int			x;

	if (!argv)
		return (3);
	x = 0;
	while ( x < argc - 3)
	{
		create_pipe(fd);
		pid =  create_fork();

		if (pid == 0) //write the file1 
		{
			child(argc, argv, fd, x);
		}
		x++;	
		//parent
		waitpid(pid, NULL, 0);
		close(fd[1]);
		if (x != argc - 3)
			dup2(fd[0], STDIN_FILENO);
		
		close(fd[0]);
		printf("parent\n");
	}
	//	if (execlp("cat", "cat", NULL) < 0)
	//		return (5);

	return (0);
}