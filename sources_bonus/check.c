/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 19:50:59 by fagiusep          #+#    #+#             */
/*   Updated: 2022/01/30 19:56:21 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_envp(t_cmd *p, char *envp[])
{
	int	i;

	i = -1;
	while (envp[++i])
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
}

int	check(t_cmd *p, int argc, char *argv[], char *envp[])
{
	p->my_argc = argc;
	p->my_argv = argv;
	p->exec_arg1 = NULL;
	p->exec_arg2 = NULL;
	if (argc < 3)
	{
		write(2, "Enter incorrect number of arguments\n", 36);
		exit(1);
	}
	if (ft_strncmp("here_doc", argv[1], 8) != 0)
		not_here_doc(p, argv);
	p->file2 = open(argv[argc - 1], O_RDWR | O_CREAT, 0777);
	if (p->file2 == -1)
	{
		write(2, "Problems to open File 2\n", 24);
		exit(1);
	}
	check_envp(p, envp);
	return (0);
}
