/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fausto <fausto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:57:16 by fausto            #+#    #+#             */
/*   Updated: 2021/11/14 13:20:42 by fausto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h> //wait()
# include "libft.h"
#include <stdio.h>

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



//debug
void	print_split(char **ptr);
void	print_join(char *str);

#endif
