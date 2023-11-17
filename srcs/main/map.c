/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoviell <enoviell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 14:34:49 by riccardobor       #+#    #+#             */
/*   Updated: 2023/11/17 11:29:15 by enoviell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

char	**expand_mat(char **mat, char *str)
{
	int		len;
	char	**res;

	len = ft_matlen(mat);
	res = malloc(sizeof(char *) * (len + 2));
	ft_matcopy(mat, res, 0);
	res[len] = str;
	res[len + 1] = NULL;
	free(mat);
	return (res);
}

void	put_wall_on_space(char **mat, char *stack, char *paste)
{
	int		i;
	char	*tmp;

	i = 0;
	while (mat[i] != NULL)
	{
		tmp = mat[i];
		mat[i] = ft_strreplace(tmp, stack, paste);
		free(tmp);
		i++;
	}
}

static void	map_format(char **map)
{
	int		i;
	int		size[2];

	i = 0;
	size[1] = 0;
	while (map[i] != NULL)
	{
		size[0] = ft_strlen(map[i]);
		if (size[1] < size[0])
			size[1] = size[0];
		i++;
	}
	i = 0;
	while (map[i] != NULL)
	{
		size[0] = ft_strlen(map[i]);
		if (size[0] < size[1])
			map[i] = ft_freejoin(map[i],
					create_string(' ', size[1] - size[0]));
		i++;
	}
}

static void	map_init2(t_cube *game, char *res, char *str, int fd)
{
	char	**map;

	while (str != NULL)
	{
		res = ft_freejoin(res, str);
		str = get_next_line(fd);
		if (str == NULL && res[0] == '\n')
		{
			free(res);
			map_error("missing map");
		}
	}
	map = NULL;
	map = ft_split(res, '\n');
	put_wall_on_space(map, "\t", "    ");
	map_format(map);
	free(res);
	game->map = map;
}

int	map_init(t_cube *game, int fd)
{
	char	*str;
	char	*res;

	str = get_next_line(fd);
	if (!str)
		map_error("no map");
	while (str[0] == '\n')
	{
		free(str);
		str = get_next_line(fd);
		if (str == NULL)
			map_error("invalid map");
	}
	res = malloc(1);
	res[0] = '\0';
	if (str != NULL)
		str[ft_strlen(str)] = '\0';
	map_init2(game, res, str, fd);
	return (0);
}
