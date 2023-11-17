/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcologgi <dcologgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:34:27 by riccardobor       #+#    #+#             */
/*   Updated: 2023/11/13 15:06:35 by dcologgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static int	ft_find(char const *s1, int start, char *s2, int size)
{
	int	i;

	i = 0;
	while (i < size && s1[start] != '\0')
	{
		if (s1[start] != s2[i])
			return (0);
		i++;
		start++;
	}
	if (s1[start] != s2[i] && s1[start] == '\0')
		return (0);
	return (1);
}

static char	*createstr(char c)
{
	char	*res;

	res = ft_calloc(1, 2);
	res[0] = c;
	return (res);
}

char	*ft_strreplace(char const *src, char *stack, char *paste)
{
	int		i;
	char	*tmp;

	tmp = ft_calloc(1, 1);
	i = 0;
	while (src[i] != '\0')
	{
		if (ft_find(src, i, stack, ft_strlen(stack)))
		{
			tmp = ft_freejoin(tmp, ft_substr(paste, 0, ft_strlen(paste)));
			i += ft_strlen(stack);
		}
		else
			tmp = ft_freejoin(tmp, createstr(src[i++]));
	}
	return (tmp);
}
