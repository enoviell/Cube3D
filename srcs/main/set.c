/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcologgi <dcologgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:31:26 by riccardobor       #+#    #+#             */
/*   Updated: 2023/11/13 16:37:20 by dcologgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static void	set_we(t_player *player, char c)
{
	if (c == 'W')
	{
		player->dir[0] = -1.0;
		player->dir[1] = 0.0;
		player->cam_plane[0] = 0.0;
		player->cam_plane[1] = -0.66;
	}
	else
	{
		player->dir[0] = 1.0;
		player->dir[1] = 0.0;
		player->cam_plane[0] = 0.0;
		player->cam_plane[1] = 0.66;
	}
}

void	set_player(t_player *player, char c)
{
	if (c == 'N')
	{
		player->dir[0] = 0.0;
		player->dir[1] = -1.0;
		player->cam_plane[0] = 0.66;
		player->cam_plane[1] = -0.0;
	}
	else if (c == 'S')
	{
		player->dir[0] = 0.0;
		player->dir[1] = 1.0;
		player->cam_plane[0] = -0.66;
		player->cam_plane[1] = 0.0;
	}
	else
		set_we(player, c);
}
