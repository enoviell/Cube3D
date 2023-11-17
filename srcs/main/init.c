/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcologgi <dcologgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:31:19 by riccardobor       #+#    #+#             */
/*   Updated: 2023/11/16 16:25:05 by dcologgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static int	init_player(t_cube *game, t_player *player)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (valid_char("NWSE", game->map[i][j]))
			{
				player->pos[0] = j + 0.5;
				player->pos[1] = i + 0.5;
				set_player(player, game->map[i][j]);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	init_directions(t_cube *game, t_player *player)
{
	if (init_player(game, player) == 0)
		return ;
	game->player = player;
	find_door(game);
}

void	init_cube(t_cube *game, t_img *img, t_textures *texts, char *path)
{
	int	i;

	i = 0;
	game->mlx = mlx_init();
	while (i < 6)
		game->t[i++] = 0;
	if (parser(game, texts, path))
	{
		printf("Error\n");
		exit(127);
	}
	if (validate_map(game) != 0)
	{
		printf("Error\n");
		exit(127);
	}
	game->mlx_win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT,
			"Cube3D");
	put_wall_on_space(game->map, " ", "1");
	game->map_h = ft_matlen(game->map);
	game->map_w = ft_strlen(game->map[0]);
	img->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	game->img = img;
}

void	init_texture(t_cube *game, t_textures *texts)
{
	game->texts = texts;
	game->texts->wall_ns = game->texts->no;
	game->texts->wall_ew = game->texts->ea;
	game->a_phase = 0;
	load_text_door(game, &(game->texts->door), DOOR);
}
