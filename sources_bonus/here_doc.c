/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 20:54:22 by fagiusep          #+#    #+#             */
/*   Updated: 2022/01/19 20:54:47 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc(int fd[], char	*argv[])
{
	char	*line;
	
	if (pipe(fd) == -1)
		exit(write(1, "pipe error\n", 11));
	while (1)
	{
		write(1, "> ", 2);
		line = ft_get_next_line(STDIN_FILENO);
		if (ft_strncmp(argv[2], line, ft_strlen(argv[2])) == 0)
			break;
		write(fd[1], line, ft_strlen(line));
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
}