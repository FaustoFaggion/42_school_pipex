/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:57:16 by fausto            #+#    #+#             */
/*   Updated: 2022/01/30 17:18:46 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>

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
	int		file_error;
}				t_cmd;

void	exit_free(t_cmd *p);

char	**ft_split_shell(char const *s, char c);

char	*ft_strjoin(char const *s1, char const *s2);

size_t	ft_strlen(const char *s);

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_strdup(const char *s);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

void	cmd_not_found(t_cmd *p, int x);

void	check_envp(t_cmd *p, char *envp[], int i);

void	check_open_files(t_cmd *p, char *argv[], int argc);

#endif
