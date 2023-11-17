/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcologgi <dcologgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:53:55 by rbordin           #+#    #+#             */
/*   Updated: 2023/11/15 11:21:05 by dcologgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

void	camera_rotation(t_cube *game, double dir, double speed)
{
	double	o_dirx;
	double	o_cam_dirx;
	double	rot_dir;

	rot_dir = speed * dir;
	o_dirx = game->player->dir[0];
	game->player->dir[0] = o_dirx * cos(rot_dir)
		- game->player->dir[1] * sin(rot_dir);
	game->player->dir[1] = o_dirx * sin(rot_dir)
		+ game->player->dir[1] * cos(rot_dir);
	o_cam_dirx = game->player->cam_plane[0];
	game->player->cam_plane[0] = o_cam_dirx * cos(rot_dir)
		- game->player->cam_plane[1] * sin(rot_dir);
	game->player->cam_plane[1] = o_cam_dirx * sin(rot_dir)
		+ game->player->cam_plane[1] * cos(rot_dir);
}

void	move_up_down(t_cube *game, double dir)
{
	double	npos_x;
	double	npos_y;
	double	pos_x;
	double	pos_y;

	pos_x = game->player->pos[0];
	pos_y = game->player->pos[1];
	npos_x = pos_x + (game->player->dir[0] * MOVSPEED * dir);
	npos_y = pos_y + (game->player->dir[1] * MOVSPEED * dir);
	if (game->map[(int) npos_y][(int) npos_x] == '1')
		return ;
	if (game->map[(int) npos_y][(int) npos_x] == 'D')
		return ;
	game->player->pos[0] = npos_x;
	game->player->pos[1] = npos_y;
}

void	move_left_right(t_cube *game, double dir)
{
	double	npos_x;
	double	npos_y;

	npos_x = game->player->pos[0]
		+ (game->player->cam_plane[0] * MOVSPEED * dir);
	npos_y = game->player->pos[1]
		+ (game->player->cam_plane[1] * MOVSPEED * dir);
	if (game->map[(int) npos_y][(int) npos_x] == '1')
		return ;
	if (game->map[(int) npos_y][(int) npos_x] == 'D')
		return ;
	game->player->pos[0] = npos_x;
	game->player->pos[1] = npos_y;
}

void	open_door(t_cube *game)
{
	int	x;
	int	y;

	x = (int) game->player->pos[0];
	y = (int) game->player->pos[1];
	if (game->map[(y) + 1][x] == 'D')
		game->map[(y) + 1][x] = 'd';
	else if (game->map[(y) - 1][x] == 'D')
		game->map[(y) - 1][x] = 'd';
	else if (game->map[(y)][(x) + 1] == 'D')
		game->map[(y)][(x) + 1] = 'd';
	else if (game->map[(y)][(x) - 1] == 'D')
		game->map[(y)][(x) - 1] = 'd';
	else if (game->map[(y) + 1][x] == 'd')
		game->map[(y) + 1][x] = 'D';
	else if (game->map[(y) - 1][x] == 'd')
		game->map[(y) - 1][x] = 'D';
	else if (game->map[(y)][(x) + 1] == 'd')
		game->map[(y)][(x) + 1] = 'D';
	else if (game->map[(y)][(x) - 1] == 'd')
		game->map[(y)][(x) - 1] = 'D';
}
