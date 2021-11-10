#include "pipex.h"
#include <stdio.h>

void	ft_clear_split(char **ptr)
{
	int	i;

	i = -1;
	while (ptr[++i])
		free(ptr[i]);
	free(ptr);
}

int	fill_p(t_cmd *p, int argc, char *argv[])
{
	p->my_argc = argc;
	p->my_argv = argv;
	p->file1 = open(p->my_argv[1], O_RDONLY);
	if (p->file1 == -1)
		printf("erro open file1");
	p->file2 = open(p->my_argv[argc - 1], O_RDWR);
	if (p->file2 == -1)
		printf("erro open file1");
	return (0);
}

int	create(t_cmd *p, int fd[], int x)
{
	int	pid;

	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid < 0)
		return (2);
	if (x != 0)
	{
		free(p->exec_arg1);
		ft_clear_split(p->exec_arg2);
	}
	p->exec_arg2 = ft_split(p->my_argv[x + 2], ' ');
	p->exec_arg1 = ft_strjoin("/usr/bin/", p->exec_arg2[0]);
	return (pid);
}

int	exec_child(t_cmd *p, int fd[], int x)
{
	close(fd[0]);
	if (x == 0)
	{
		dup2(p->file1, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
	}
	else if (x == 1)
	{
		dup2(p->file2, STDOUT_FILENO);
	}
	close(fd[1]);
	if (execve(p->exec_arg1, p->exec_arg2, NULL) < 0)
		return (5);
	return (0);
}

void	finish_parent(t_cmd *p, int fd[], int pid1, int pid2)
{
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	ft_clear_split(p->exec_arg2);
	free(p->exec_arg1);
	close(fd[1]);
	close(fd[0]);
	printf("Finish parent\n");
}

int	main(int argc, char *argv[])
{
	t_cmd		p;
	int			fd[2];
	int			pid1;
	int			pid2;

	if (argc != 5)
		return (1);
	fill_p(&p, argc, argv);
	pid1 = create(&p, fd, 0);
	if (pid1 == 0)
		exec_child(&p, fd, 0);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	pid2 = create(&p, fd, 1);
	if (pid2 == 0)
		exec_child(&p, fd, 1);
	finish_parent(&p, fd, pid1, pid2);
	return (0);
}
