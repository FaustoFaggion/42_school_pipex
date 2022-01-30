/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 20:54:22 by fagiusep          #+#    #+#             */
/*   Updated: 2022/01/30 19:47:22 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	wr_line(char *argv[], int limiter, int fd[])
{
	char	*line;

	while (1)
	{
		write(1, "> ", 2);
		line = ft_get_next_line(STDIN_FILENO);
		if (ft_strncmp(argv[2], line, limiter) == 0)
		{
			if (line[limiter] == '\n')
			{
				free(line);
				ft_get_next_line(-1);
				break ;
			}
			write(fd[1], line, ft_strlen(line));
		}
		else
		{
			write(fd[1], line, ft_strlen(line));
		}
		free(line);
	}
}

int	here_doc(int fd[], char	*argv[])
{
	int		limiter;

	if (ft_strncmp("here_doc", argv[1], 8) == 0)
	{
		if (pipe(fd) == -1)
			exit(write(1, "pipe error\n", 11));
		limiter = ft_strlen(argv[2]);
		wr_line(argv, limiter, fd);
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		return (3);
	}
	return (2);
}

void	not_here_doc(t_cmd *p, char *argv[])
{
	p->file1 = open(argv[1], O_RDONLY);
	if (p->file1 == -1)
	{
		write(2, "Problems to open File 1\n", 24);
		exit(1);
	}
}
