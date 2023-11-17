/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcologgi <dcologgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:35:18 by rbordin           #+#    #+#             */
/*   Updated: 2023/11/15 11:21:05 by dcologgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

int	key_filter(int keycode, t_cube *game)
{
	if (keycode == 65307)
		end_game(game);
	else if (keycode == 'w')
		move_up_down(game, 1.0);
	else if (keycode == 's')
		move_up_down(game, -1.0);
	else if (keycode == 65361)
		camera_rotation(game, -1.0, ROTSPEED);
	else if (keycode == 65363)
		camera_rotation(game, 1.0, ROTSPEED);
	else if (keycode == 'a')
		move_left_right(game, -1.0);
	else if (keycode == 'd')
		move_left_right(game, 1.0);
	else if (keycode == 0x20)
		open_door(game);
	return (0);
}
