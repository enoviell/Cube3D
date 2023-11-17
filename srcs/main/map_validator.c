/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcologgi <dcologgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:34:54 by riccardobor       #+#    #+#             */
/*   Updated: 2023/11/14 17:07:51 by dcologgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

void	map_error(char *error)
{
	printf("%s\n", error);
	exit(-1);
}

static int	body(char **map, int x, int y)
{
	int	res;

	res = 0;
	if (map[y][x] != '-' && map[y][x] != '1')
	{
		if (map[y][x + 1] == '\0' || map[y + 1] == NULL ||
				x - 1 < 0 || y - 1 < 0)
			res = 1;
		else
		{
			map[y][x] = '-';
			if (map[y][x + 1] != '1')
				res = body(map, x + 1, y);
			if (map[y][x - 1] != '1' && res != 1)
				res = body(map, x - 1, y);
			if (map[y + 1][x] != '1' && res != 1)
				res = body(map, x, y + 1);
			if (map[y - 1][x] != '1' && res != 1)
				res = body(map, x, y - 1);
		}
	}
	return (res);
}

static int	flood_algorithm(char **map)
{
	int	pl[2];

	find_char(map, pl);
	return (body(map, pl[0], pl[1]));
}

static int	np(t_cube *game)
{
	int	i;
	int	j;
	int	n;
	int	d;

	i = -1;
	n = 0;
	d = 0;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
		{
			if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'E' || game->map[i][j] == 'W')
				n++;
			else if (game->map[i][j] == 'D')
				d++;
		}
	}
	game->door = ft_calloc(d, sizeof(t_door));
	if (n != 1)
		return (0);
	return (1);
}

int	validate_map(t_cube *game)
{
	int		i;
	int		j;
	int		res;
	char	**map2;

	i = -1;
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j] != '\0')
		{
			if (!valid_char("NWES01D \n", game->map[i][j]) || !np(game))
				return (1);
		}
	}
	if (ft_matlen(game->map) < 3)
		map_error("map not valid");
	map2 = malloc(sizeof(char *) * (ft_matlen(game->map) + 1));
	ft_matcopy(game->map, map2, 0);
	res = flood_algorithm(map2);
	free_mat(map2);
	return (res);
}
