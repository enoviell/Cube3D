/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoviell <enoviell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:31:04 by riccardobor       #+#    #+#             */
/*   Updated: 2023/11/17 10:50:34 by enoviell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

int	end_game(t_cube *game)
{
	free_mat(game->map);
	free(game->door);
	exit(0);
}

static int	game_loop(t_cube *game)
{
	t_ray		ray;
	static int	lock = 0;

	if (lock == 100)
	{
		ft_memset(&ray, 0, sizeof(t_ray));
		raycast(game, game->img, &ray);
		render_minimap(game);
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->img->img, 0, 0);
		lock = 0;
	}
	else
		lock++;
	return (0);
}

static int	argv_check(char *argv)
{
	int	i;

	if (!argv)
		return (0);
	i = 0;
	while (argv[i])
		i++;
	i -= 1;
	if (argv[i] == 'b' && argv[i - 1] == 'u'
		&& argv[i - 2] == 'c' && argv[i - 3] == '.')
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cube			game;
	t_player		player;
	t_img			img;
	t_textures		texts;

	if (argc != 2)
		return (printf("Error: bad arguments.\n"));
	if (argv_check(argv[1]) == 0)
		return (printf("Error: Invalid  format\n"));
	init_cube(&game, &img, &texts, argv[1]);
	init_texture(&game, &texts);
	init_directions(&game, &player);
	mlx_hook(game.mlx_win, 17, 0, end_game, &game);
	mlx_hook(game.mlx_win, 2, 1L << 0, key_filter, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
}
