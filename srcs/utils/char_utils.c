/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcologgi <dcologgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:32:55 by riccardobor       #+#    #+#             */
/*   Updated: 2023/11/14 17:06:15 by dcologgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

void	find_char(char **map, int *ids)
{
	ids[1] = 0;
	while (map[ids[1]] != NULL)
	{
		ids[0] = 0;
		while (map[ids[1]][ids[0]] != '\0')
		{
			if (valid_char("NSWE", map[ids[1]][ids[0]]))
				return ;
			ids[0]++;
		}
		ids[1]++;
	}
	ids[1] = -1;
	ids[0] = -1;
}

int	valid_char(const char *stack, char c)
{
	int	i;

	i = 0;
	if (stack == NULL)
		return (0);
	while (stack[i] != '\0')
	{
		if (stack[i] == c)
			return (1);
		i++;
	}
	return (0);
}
