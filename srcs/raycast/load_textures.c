/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcologgi <dcologgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:42:49 by rbordin           #+#    #+#             */
/*   Updated: 2023/11/14 17:05:26 by dcologgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

int	load_text_walls(t_cube *game, t_tex *tex, char **path, int pos)
{
	game->t[pos] = 0;
	tex->xpm.img = mlx_xpm_file_to_image(game->mlx, path[1],
			&tex->w, &tex->h);
	if (!tex->xpm.img)
		return (1);
	tex->xpm.addr = mlx_get_data_addr(tex->xpm.img,
			&tex->xpm.bits_per_pixel, &tex->xpm.line_length,
			&tex->xpm.endian);
	if (!tex->xpm.addr)
		return (1);
	game->t[pos] = 1;
	return (0);
}

int	load_text_door(t_cube *game, t_tex *tex, char *path)
{
	tex->xpm.img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->w, &tex->h);
	if (!tex->xpm.img)
		return (1);
	tex->xpm.addr = mlx_get_data_addr(tex->xpm.img,
			&tex->xpm.bits_per_pixel, &tex->xpm.line_length,
			&tex->xpm.endian);
	if (!tex->xpm.addr)
		return (1);
	return (0);
}

void	find_door(t_cube *game)
{
	int			x;
	int			y;
	int			z;

	y = -1;
	z = 0;
	while (game->map[++y])
	{
		x = -1;
		while (game->map[y][++x] != '\0')
		{
			if (game->map[y][x] == 'D')
			{
				game->door[z].x = x;
				game->door[z].y = y;
				z++;
			}
		}
	}
}
