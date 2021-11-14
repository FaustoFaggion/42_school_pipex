/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fausto <fausto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:26:30 by fausto            #+#    #+#             */
/*   Updated: 2021/11/14 13:26:31 by fausto           ###   ########.fr       */
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
	perror(NULL);
	exit(write(2, "já era\n", 8));
}
