/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgbutility.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcologgi <dcologgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:32:36 by riccardobor       #+#    #+#             */
/*   Updated: 2023/11/14 16:19:32 by dcologgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

unsigned long	create_rgb(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

int	get_rgb(char *addr, int x, int y)
{
	int	rgb[3];

	rgb[0] = addr[(x * 4) + (y * 64 * 4) + 2];
	rgb[1] = addr[(x * 4) + (y * 64 * 4) + 1];
	rgb[2] = addr[(x * 4) + (y * 64 * 4)];
	return (0x00FFFFFF & (rgb[0] << 16 | rgb[1] << 8 | rgb[2]));
}

static int	load_error(char **rgbb)
{
	free_mat(rgbb);
	return (1);
}

unsigned long	get_pixel(t_img *img, int x, int y)
{
	char	*dest;

	if (x < 0 || x >= 64 || y < 0 || y >= 64)
		return (1);
	dest = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned long *)dest);
}

int	load_background(t_cube *game, char **s, char c, int pos)
{
	int		i;
	char	**rgbb;

	rgbb = ft_split(s[1], ',');
	if (ft_matlen(rgbb) != 3)
		return (load_error(rgbb));
	i = -1;
	while (i++ < 2)
	{
		if (c == 'F')
			game->f[i] = ft_atoi(rgbb[i]);
		else
			game->c[i] = ft_atoi(rgbb[i]);
	}
	free_mat(rgbb);
	game->t[pos] = 1;
	return (0);
}
