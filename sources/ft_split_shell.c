/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_shell_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 09:57:37 by fausto            #+#    #+#             */
/*   Updated: 2022/01/30 10:19:08 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static size_t	ft_ptr_count_shell(char const *s, char c)
{
	size_t	i;
	size_t	nb;

	i = 0;
	nb = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] == '\'')
		{
			nb++;
			i++;
			while (s[i] != '\'' && s[i] != '\0')
				i++;
			i++;
		}
		if (s[i] != c && s[i] != '\0' && (s[i] != '\''))
		{	
			nb++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (nb);
}

static char	**free_tab(char **tab, size_t i)
{
	while ((int)i >= 0)
	{
		free(tab[i]);
		tab[i] = NULL;
		i--;
	}
	free(tab);
	tab = NULL;
	return (tab);
}

int	len_s(char const *s, char c, int j)
{
	int	len_ptr;

	len_ptr = 0;
	if (s[j] == '\'')
	{
		j++;
		while (s[len_ptr + j] != '\'' && s[len_ptr + j] != 0)
			len_ptr++;
	}
	else if (s[j] != c && s[j] != '\'')
	{
		while (s[len_ptr + j] != c && s[len_ptr + j] != 0)
			len_ptr++;
	}
	return (len_ptr);
}

static void	mal_sub(char **tab, char const *s, char c, size_t nb_ptr)
{
	size_t	len_ptr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < nb_ptr)
	{
		if (s[j] == c)
			j++;
		else
		{
			len_ptr = len_s(s, c, j);
			if (s[j] == '\'')
				j++;
			tab[i] = ft_substr(s, j, len_ptr);
			if (tab[i] == NULL)
				free_tab(tab, i);
			j = j + len_ptr;
			i++;
		}
	}
	tab[i] = NULL;
}

char	**ft_split_shell(char const *s, char c)
{
	char	**tab;
	size_t	nb_ptr;

	if (!s)
		return (NULL);
	nb_ptr = ft_ptr_count_shell(s, c);
	tab = (char **)malloc(((sizeof(char *)) * (nb_ptr + 1)));
	if (!tab)
		return (NULL);
	mal_sub(tab, s, c, nb_ptr);
	return (tab);
}
