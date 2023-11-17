/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcologgi <dcologgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:32:29 by riccardobor       #+#    #+#             */
/*   Updated: 2023/11/15 11:38:02 by dcologgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static void	init_ray(t_cube *game, t_ray *ray)
{
	game->player->cam_side = (2.0 * ((double) ray->ray_id)
			/ ((double) WIN_WIDTH)) - 1;
	ray->dir[0] = game->player->dir[0]
		+ game->player->cam_plane[0] * game->player->cam_side;
	ray->dir[1] = game->player->dir[1]
		+ game->player->cam_plane[1] * game->player->cam_side;
	ray->pos[0] = (int) game->player->pos[0];
	ray->pos[1] = (int) game->player->pos[1];
	if (ray->dir[0] == 0)
		ray->delta_dist[0] = 1e30;
	else
		ray->delta_dist[0] = absf(1.0 / ray->dir[0]);
	if (ray->dir[1] == 0)
		ray->delta_dist[1] = 1e30;
	else
		ray->delta_dist[1] = absf(1.0 / ray->dir[1]);
}

static void	set_next_border(t_cube *game, t_ray *ray)
{
	if (ray->dir[0] < 0)
	{
		ray->incr[0] = -1;
		ray->side_dist[0] = (game->player->pos[0]
				- ((double) ray->pos[0])) * ray->delta_dist[0];
	}
	else
	{
		ray->incr[0] = 1;
		ray->side_dist[0] = (((double) ray->pos[0]) + 1.0
				- game->player->pos[0]) * ray->delta_dist[0];
	}
	if (ray->dir[1] < 0)
	{
		ray->incr[1] = -1;
		ray->side_dist[1] = (game->player->pos[1]
				- ((double) ray->pos[1])) * ray->delta_dist[1];
	}
	else
	{
		ray->incr[1] = 1;
		ray->side_dist[1] = (((double) ray->pos[1]) + 1.0
				- game->player->pos[1]) * ray->delta_dist[1];
	}
}

static void	calc_proportions(t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_dist = ray->side_dist[0] - ray->delta_dist[0];
	else
		ray->wall_dist = ray->side_dist[1] - ray->delta_dist[1];
	ray->wall_height = (int) WIN_HEIGHT / (ray->wall_dist);
	ray->draw[0] = (WIN_HEIGHT / 2) - (ray->wall_height / 2);
	ray->draw[1] = (WIN_HEIGHT / 2) + (ray->wall_height / 2);
	if (ray->draw[0] < 0)
		ray->draw[0] = 0;
	if (ray->wall_dist <= 0)
	{
		ray->wall_height = WIN_HEIGHT;
		ray->wall_dist = 0;
	}
	if (ray->draw[1] >= WIN_HEIGHT)
		ray->draw[1] = WIN_HEIGHT - 1;
}

static void	define_wall_height(t_cube *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->wallx = game->player->pos[1] + ray->wall_dist * ray->dir[1];
	else
		ray->wallx = game->player->pos[0] + ray->wall_dist * ray->dir[0];
	ray->wallx -= floor(ray->wallx);
	ray->texx = (int)(ray->wallx * 64.0);
	if (ray->side == 0 && ray->dir[0] > 0)
		ray->texx = 64 - ray->texx - 1;
	if (ray->side == 1 && ray->dir[1] < 0)
		ray->texx = 64 - ray->texx - 1;
	ray->step = 1.0 * 64.0 / ((double) ray->wall_height);
	ray->texpos = (((double) ray->draw[0]) - WIN_HEIGHT / 2
			+ ray->wall_height / 2) * ray->step;
}

int	raycast(t_cube *game, t_img *img, t_ray *ray)
{
	int		i;

	i = 0;
	while (i < WIN_WIDTH)
	{
		ray->ray_id = i;
		init_ray(game, ray);
		set_next_border(game, ray);
		found_wall(game, ray);
		calc_proportions(ray);
		define_wall_height(game, ray);
		draw_pixel_column(game, i, ray, img);
		i++;
	}
	display_cross(img);
	return (0);
}
