/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fausto <fausto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 09:57:13 by fausto            #+#    #+#             */
/*   Updated: 2021/11/15 09:57:14 by fausto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
