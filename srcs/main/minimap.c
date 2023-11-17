/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcologgi <dcologgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:35:30 by riccardobor       #+#    #+#             */
/*   Updated: 2023/11/15 11:16:10 by dcologgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static void	draw_minimap(t_cube *game, int start_x, int x)
{
	int	start_y;
	int	y;
	int	pix[2];

	start_y = (int) floor(game->player->pos[1]);
	y = start_y + PLAYER_R;
	pix[0] = 50 + ((x - start_x) * 10);
	while (y >= start_y - 4)
	{
		pix[1] = 50 - ((start_y - y) * 10);
		if (x < 0 || y < 0 || y >= game->map_h
			|| x >= game->map_w)
			outside_square(game->img, 10, pix[0] + 10, pix[1]);
		else if (game->map[y][x] == '1')
			wall_square(game->img, 10, pix[0] + 10, pix[1]);
		else if (game->map[y][x] == 'D')
			door_square(game->img, 10, pix[0] + 10, pix[1]);
		else if (game->map[y][x] != '1')
			floor_square(game->img, 10, pix[0] + 10, pix[1]);
		y--;
	}
}

void	render_minimap(t_cube *game)
{
	int	start_x;
	int	x;

	start_x = (int) floor(game->player->pos[0]);
	x = start_x + PLAYER_R;
	while (x >= start_x - 4)
	{
		draw_minimap(game, start_x, x);
		x--;
	}
	player_square(game->img, 10, 60, 50);
}
