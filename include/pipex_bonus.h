/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 18:20:33 by fagiusep          #+#    #+#             */
/*   Updated: 2022/01/29 12:35:13 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
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

char	*ft_strjoin(char const *s1, char const *s2);

size_t	ft_strlen(const char *s);

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_strdup(const char *s);

char	*ft_get_next_line(int fd);

char	*ft_strchr(const char *s, int c);

#endif
