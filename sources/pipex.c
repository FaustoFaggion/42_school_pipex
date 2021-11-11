#include "pipex.h"
#include <stdio.h>

int	check(t_cmd *p, int argc, char *argv[])
{
	if (argc != 5)
		return(write(1, "Enter incorrect number of arguments\n", 36));
	p->file1 = open(argv[1], O_RDONLY);
	if (p->file1 == -1)
		return(write(1, "Problems to open File 1\n", 24));
	p->file2 = open(argv[argc - 1], O_RDWR);
	if (p->file2 == -1)
		return(write(1, "Problems to open File 2\n", 24));
	p->my_argc = argc;
	p->my_argv = argv;
	p->exec_arg1 = NULL;
	p->exec_arg2 = NULL;
	return (0);
}

int	exec_child(t_cmd *p, int fd[], int x)
{
	close(fd[0]);
	if (x == 2)
	{
		dup2(p->file1, STDIN_FILENO);
		printf("open %d x=%d\n", p->file1, x);
	}
	if (x == 3)
		dup2(p->file2, STDOUT_FILENO);
	else
		dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (execve(p->exec_arg1, p->exec_arg2, NULL) < 0)
		return (write(1, "error execve\n", 13));
	return (0);
}

void	parent(t_cmd *p, int fd[])
{
	int	i;

	dup2(fd[0], STDIN_FILENO);
	free(p->exec_arg1);
	i = -1;
	while (p->exec_arg2[++i])
		free(p->exec_arg2[i]);
	free(p->exec_arg2);
	close(fd[0]);
	close(fd[1]);
}

int	main(int argc, char *argv[])
{
	t_cmd	p;
	int		fd[2];
	int		pid;
	int		x;

	check(&p, argc, argv);
	x = 2;
	while (x < argc - 1)
	{
		if (pipe(fd) == -1)
			return(write(1, "pipe error\n", 11));
		p.exec_arg2 = ft_split(p.my_argv[x], ' ');
		p.exec_arg1 = ft_strjoin("/usr/bin/", p.exec_arg2[0]);
		pid = fork();
		if (pid < 0)
			return(write(1, "fork error\n", 11));
		if (pid == 0)
			exec_child(&p, fd, x);
		waitpid(pid, NULL, 0);
		parent(&p, fd);
		x++;
	}
	return (0);
}