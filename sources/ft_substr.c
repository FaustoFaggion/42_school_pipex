/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fagiusep <fagiusep@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/13 15:19:12 by fagiusep          #+#    #+#             */
/*   Updated: 2021/08/13 15:19:12 by fagiusep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	size;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if ((ft_strlen(s) - start) < len)
		size = (ft_strlen(s) - start) + 1;
	else
		size = len + 1;
	substr = (char *)malloc(size * sizeof(char));
	if (!substr)
	{
		return (NULL);
	}
	ft_strlcpy(substr, &s[start], size);
	return (substr);
}
