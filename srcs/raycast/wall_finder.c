/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcologgi <dcologgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:31:59 by riccardobor       #+#    #+#             */
/*   Updated: 2023/11/15 11:30:12 by dcologgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static void	find_wall(t_cube *game, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist[0] < ray->side_dist[1])
		{
			ray->side_dist[0] += ray->delta_dist[0];
			ray->pos[0] += ray->incr[0];
			ray->side = 0;
		}
		else
		{
			ray->side_dist[1] += ray->delta_dist[1];
			ray->pos[1] += ray->incr[1];
			ray->side = 1;
		}
		if (game->map[(ray->pos[1])][(ray->pos[0])] == '1' ||
			game->map[(ray->pos[1])][(ray->pos[0])] == 'D')
			hit = 1;
	}
}

void	found_wall(t_cube *game, t_ray *ray)
{
	if (game->map[(ray->pos[1])][(ray->pos[0])] == '1')
	{
		if (ray->side_dist[0] < ray->side_dist[1])
			ray->side = 0;
		else
			ray->side = 1;
		return ;
	}
	else
		find_wall(game, ray);
}
