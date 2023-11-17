/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcologgi <dcologgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:35:01 by riccardobor       #+#    #+#             */
/*   Updated: 2023/11/13 15:06:35 by dcologgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

void	free_mat(char **mat)
{
	int	i;

	i = 0;
	while (mat[i] != NULL)
		free(mat[i++]);
	free(mat);
}

int	ft_matlen(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

void	ft_matcopy(char **src, char **dst, int start)
{
	int	i;

	i = 0;
	if (!src || !dst || start < 0)
		return ;
	while (src[i] != NULL)
	{
		dst[start] = ft_substr(src[i], 0, ft_strlen(src[i]));
		i++;
		start++;
	}
	dst[start] = NULL;
}
