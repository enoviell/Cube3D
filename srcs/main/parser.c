/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcologgi <dcologgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 10:05:15 by rbordin           #+#    #+#             */
/*   Updated: 2023/11/16 16:22:53 by dcologgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static int	parse_error(int fd, char *str)
{
	close(fd);
	free(str);
	return (1);
}

static int	filter(t_cube *game, t_textures *texts, char **split)
{
	if (!ft_strcmp(split[0], "NO"))
		return (load_text_walls(game, &(texts->no), split, 0));
	else if (!ft_strcmp(split[0], "SO"))
		return (load_text_walls(game, &(texts->so), split, 1));
	else if (!ft_strcmp(split[0], "WE"))
		return (load_text_walls(game, &(texts->we), split, 2));
	else if (!ft_strcmp(split[0], "EA"))
		return (load_text_walls(game, &(texts->ea), split, 3));
	else if (!ft_strcmp(split[0], "F"))
		return (load_background(game, split, 'F', 4));
	else if (!ft_strcmp(split[0], "C"))
		return (load_background(game, split, 'C', 5));
	return (1);
}

static int	checker(int *t)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (t[i] != 1)
			return (0);
		i++;
	}
	return (1);
}

static int	parser_two(t_cube *game, t_textures *texts, char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	if (ft_matlen(split) != 2)
	{
		free_mat(split);
		return (1);
	}
	split[1][ft_strlen(split[1]) - 1] = '\0';
	if (filter(game, texts, split))
	{
		free_mat(split);
		return (1);
	}
	free_mat(split);
	return (0);
}

int	parser(t_cube *game, t_textures *texts, char *path)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	line = NULL;
	while (!checker(game->t))
	{
		line = get_next_line(fd);
		if (!line)
			return (parse_error(fd, NULL));
		if (!ft_strcmp(line, "\n"))
		{
			free(line);
			continue ;
		}
		if (parser_two(game, texts, line))
			return (parse_error(fd, line));
		free(line);
	}
	if (map_init(game, fd) || !line)
		return (parse_error(fd, line));
	return (0);
}
