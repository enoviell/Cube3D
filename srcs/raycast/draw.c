/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcologgi <dcologgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:32:06 by riccardobor       #+#    #+#             */
/*   Updated: 2023/11/15 11:32:46 by dcologgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static void	draw_ceiling(t_cube *game, int x, t_ray *ray, t_img *img)
{
	int	v;

	v = 0;
	while (v < ray->draw[0])
	{
		my_mlx_pixel_put(img, x, v,
			create_rgb(game->c[0], game->c[1], game->c[2]));
		v++;
	}
}

static void	draw_floor(t_cube *game, int x, t_ray *ray, t_img *img)
{
	int	v;

	v = ray->draw[1];
	while (v < WIN_HEIGHT)
	{
		my_mlx_pixel_put(img, x, v,
			create_rgb(game->f[0], game->f[1], game->f[2]));
		v++;
	}
}

static unsigned long int	get_color(t_cube *game, t_ray *ray, int texy)
{
	unsigned long int	color;

	color = 0;
	if (game->map[(ray->pos[1])][(ray->pos[0])] == 'D')
		color = get_pixel(&game->texts->door.xpm, ray->texx, texy);
	else if (ray->side == 0)
	{
		if (game->player->pos[0] - ray->pos[0] > 0)
			color = get_pixel(&game->texts->we.xpm, ray->texx, texy);
		else
			color = get_pixel(&game->texts->ea.xpm, ray->texx, texy);
	}
	else
	{
		if (game->player->pos[1] - ray->pos[1] > 0)
			color = get_pixel(&game->texts->no.xpm, ray->texx, texy);
		else
			color = get_pixel(&game->texts->so.xpm, ray->texx, texy);
	}
	return (color);
}

void	draw_pixel_column(t_cube *game, int x, t_ray *ray, t_img *img)
{
	int					v;
	unsigned long int	color;
	int					texy;

	draw_ceiling(game, x, ray, img);
	v = ray->draw[0];
	color = 0;
	while (v < ray->draw[1])
	{
		texy = (int) ray->texpos & (64 - 1);
		ray->texpos += ray->step;
		color = get_color(game, ray, texy);
		my_mlx_pixel_put(img, x, v, color);
		v++;
	}
	draw_floor(game, x, ray, img);
}

void	display_cross(t_img *img)
{
	int	i;

	i = 0;
	while (i++ < 20)
		my_mlx_pixel_put(img, (WIN_WIDTH / 2) + (i * -1), WIN_HEIGHT / 2,
			0x00F0F8FF);
	i = 0;
	while (i++ < 20)
		my_mlx_pixel_put(img, (WIN_WIDTH / 2) + i, WIN_HEIGHT / 2, 0x00F0F8FF);
	i = 0;
	while (i++ < 20)
		my_mlx_pixel_put(img, WIN_WIDTH / 2, (WIN_HEIGHT / 2) + (i * -1),
			0x00F0F8FF);
	i = 0;
	while (i++ < 20)
		my_mlx_pixel_put(img, WIN_WIDTH / 2, (WIN_HEIGHT / 2) + i, 0x00F0F8FF);
}
