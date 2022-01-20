/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 18:20:33 by fagiusep          #+#    #+#             */
/*   Updated: 2022/01/19 21:20:30 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include "libft.h"
# include <stdio.h>

typedef struct s_cmd
{
	char	**my_argv;
	char	**my_envp;
	int		my_argc;
	int		file1;
	int		file2;
	char	*exec_arg1;
	char	*swap;
	char	**exec_arg2;
}				t_cmd;

void	exit_free(t_cmd *p);

char	**ft_split_shell(char const *s, char c);

int		here_doc(int fd[], char	*argv[]);

void	not_here_doc(t_cmd *p, char *argv[]);

#endif
