/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fausto <fausto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:26:58 by fausto            #+#    #+#             */
/*   Updated: 2021/11/14 16:19:58 by fausto           ###   ########.fr       */
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

static void	mal_sub(char **tab, char const *s, char c, size_t nb_ptr)
{
	size_t	len_ptr;
	size_t	i;

	i = 0;
	while (i < nb_ptr)
	{
		if (*s == c)
			s++;
		else
		{
			len_ptr = 0;
			if (*s == '\'')
			{
				s++;
				while (s[len_ptr] != '\'' && s[len_ptr] != 0)
				len_ptr++;
			}
			else if (*s != c && *s != '\'')
			{
				while (s[len_ptr] != c && s[len_ptr] != 0)
					len_ptr++;
			}
			tab[i] = ft_substr(s, 0, len_ptr);
			if (tab[i] == NULL)
				free_tab(tab, i);
			s = s + len_ptr;
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
