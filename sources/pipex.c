/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 18:20:41 by fagiusep          #+#    #+#             */
/*   Updated: 2022/01/30 17:15:47 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	cmd_setup(t_cmd *p, int x)
{
	int		i;
	char	*swap;

	p->exec_arg2 = ft_split_shell(p->my_argv[x], ' ');
	if (p->exec_arg2 == NULL)
		exit_free(p);
	i = -1;
	while (p->my_envp[++i])
	{
		p->exec_arg1 = ft_strjoin(p->my_envp[i], "/");
		if (p->exec_arg1 == NULL)
			exit_free(p);
		swap = p->exec_arg1;
		p->exec_arg1 = ft_strjoin(swap, p->exec_arg2[0]);
		free(swap);
		if (p->exec_arg1 == NULL)
			exit_free(p);
		if (access(p->exec_arg1, F_OK) == 0)
			return (0);
		free(p->exec_arg1);
		p->exec_arg1 = NULL;
	}
	cmd_not_found(p, x);
	return (1);
}

int	check(t_cmd *p, int argc, char *argv[], char *envp[])
{
	int	i;

	p->my_argc = argc;
	p->my_argv = argv;
	p->exec_arg1 = NULL;
	p->exec_arg2 = NULL;
	p->file_error = 0;
	if (argc != 5)
	{
		write(2, "Enter incorrect number of arguments\n", 36);
		exit(1);
	}
	check_open_files(p, argv, argc);
	i = -1;
	while (envp[++i])
		check_envp(p, envp, i);
	return (0);
}

int	exec_child(t_cmd *p, int fd[], int x)
{
	close(fd[0]);
	if (x == 2)
		dup2(p->file1, STDIN_FILENO);
	if (x == p->my_argc - 2)
		dup2(p->file2, STDOUT_FILENO);
	else
		dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (execve(p->exec_arg1, p->exec_arg2, NULL) == -1)
	{
		write(2, "error execve\n", 13);
		exit(1);
	}
	return (0);
}

void	parent(t_cmd *p, int fd[], int x)
{
	int	i;

	p->file_error = 0;
	dup2(fd[0], STDIN_FILENO);
	free(p->exec_arg1);
	i = -1;
	while (p->exec_arg2[++i])
		free(p->exec_arg2[i]);
	free(p->exec_arg2);
	if (x == p->my_argc - 2)
	{
		i = -1;
		while (p->my_envp[++i])
			free(p->my_envp[i]);
		free(p->my_envp);
	}
	close(fd[0]);
	close(fd[1]);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_cmd	p;
	int		fd[2];
	int		pid;
	int		x;

	check(&p, argc, argv, envp);
	x = 2;
	while (x < argc - 1)
	{
		if (pipe(fd) == -1)
			exit(write(1, "pipe error\n", 11));
		if (cmd_setup(&p, x) == 0 && p.file_error == 0)
		{
			pid = fork();
			if (pid < 0)
				exit(write(1, "fork error\n", 11));
			if (pid == 0)
				exec_child(&p, fd, x);
			waitpid(pid, NULL, 0);
		}
		parent(&p, fd, x);
		x++;
	}
	return (0);
}
