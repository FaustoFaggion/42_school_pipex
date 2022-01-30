/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 09:57:13 by fausto            #+#    #+#             */
/*   Updated: 2022/01/30 17:10:19 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_free(t_cmd *p)
{
	int	i;

	if (p->exec_arg2 != NULL)
	{
		i = -1;
		while (p->exec_arg2[++i])
			free(p->exec_arg2[i]);
		free(p->exec_arg2);
	}
	if (p->my_envp != NULL)
	{
		i = -1;
		while (p->my_envp[++i])
			free(p->my_envp[i]);
		free(p->my_envp);
	}
	exit(127);
}

void	cmd_not_found(t_cmd *p, int x)
{
	write(1, p->exec_arg2[0], ft_strlen(p->exec_arg2[0]));
	write(1, ": Command not found\n", 20);
	if (x == (p->my_argc - 2))
		exit_free(p);
}

void	check_open_files(t_cmd *p, char *argv[], int argc)
{
	p->file2 = open(argv[argc - 1], O_RDWR | O_CREAT, 0777);
	if (p->file2 == -1)
	{
		perror(argv[argc - 1]);
		exit(1);
	}
	p->file1 = open(argv[1], O_RDONLY);
	if (p->file1 == -1)
	{
		perror(argv[1]);
		p->file_error = 1;
	}
}

void	check_envp(t_cmd *p, char *envp[], int i)
{
	if (ft_strncmp("PATH=", envp[i], 5) == 0)
	{
		p->my_envp = ft_split_shell(envp[i], ':');
		if (p->my_envp == NULL)
		{
			write(2, "ft_split error on function check\n", 33);
			exit(1);
		}
	}
}
