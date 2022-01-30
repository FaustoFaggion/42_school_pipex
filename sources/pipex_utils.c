/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 09:57:13 by fausto            #+#    #+#             */
/*   Updated: 2022/01/30 13:50:51 by fagiusep         ###   ########.fr       */
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

void cmd_not_found(t_cmd *p, int x)
{
	write(1, p->exec_arg2[0], ft_strlen(p->exec_arg2[0]));
	write(1, ": Command not found\n", 20);
	if (x == (p->my_argc - 2))
		exit_free(p);
}