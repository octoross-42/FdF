/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:44:16 by octoross          #+#    #+#             */
/*   Updated: 2023/12/05 19:44:16 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "constantes.h"

int	ft_open_map(int *fd, char *path, char **line)
{
	*fd = open(path, O_RDONLY);
	if ((*fd) < 0)
		return (ft_printf(ERR_OPEN, path), 1);
	*line = gnl(*fd);
	if (!(*line))
		return (ft_printf(ERR_EMPTY, path), 1);
	return (0);
}

int	ft_map_dimension(int *fd, char *path, t_map	*map)
{
	char	*line;
	int		j;

	if (ft_open_map(fd, path, &line) == 1)
		return (1);
	map->i = 0;
	while (line)
	{
		j = ft_len_line(line);
		free(line);
		if (j < 0)
			return (1);
		if (map->i == 0)
			map->j = j;
		else if (map->j != j)
			return (close(*fd), ft_printf(ERR_MAP, path, map->i, j, map->j), 1);
		map->i ++;
		line = gnl(*fd);
	}
	return (close(*fd), 0);
}

t_wire	**ft_fill_line(t_map *map, int *i, int *j, char **splited)
{
	t_wire		**map_line;
	t_altitude	altitude;

	map_line = (t_wire **)malloc(sizeof(t_wire *) * (map->j));
	if (!(map_line))
		return (ft_printf(ERR_MALLOC), NULL);
	while (splited[*j] && splited[*j][0] != '\n')
	{
		altitude = ft_read_altitude(splited[*j]);
		if (!altitude.is_valid)
			return (ft_printf(ERR_FORMAT,
					splited[*j], *i, *j), NULL);
		map_line[*j] = ft_wire(*i, *j, altitude);
		if (!(map_line[*j]))
			return ((*i)++, NULL);
		ft_update_density(map, map_line[*j]);
		if ((*i == 0 && *j == 0) || (map->min_altitude > altitude.z))
			map->min_altitude = altitude.z;
		if ((*i == 0 && *j == 0) || (map->max_altitude < altitude.z))
			map->max_altitude = altitude.z;
		(*j)++;
	}
	return (map_line);
}

int	ft_fill_map(int fd, t_map *map, char *line)
{
	char	**splited;
	int		i;
	int		j;

	map->wires = (t_wire ***)malloc(sizeof(t_wire **) * (map->i));
	if (!(map->wires))
		return (free(line), free(map), ft_printf(ERR_MALLOC), 1);
	i = 0;
	while (line)
	{
		splited = ft_split(line, ' ');
		j = 0;
		if (!splited)
			return (free(line), ft_clear_map(map, j, 0), ft_printf(ERR_MALLOC), 1);
		map->wires[i] = ft_fill_line(map, &i, &j, splited);
		ft_free_until((void **)splited, -1);
		free(line);
		if (!(map->wires[i]))
			return (ft_clear_map(map, i, j), 1);
		line = gnl(fd);
		i ++;
	}
	return (0);
}

t_map	*ft_get_map(char *path, int argc, char **argv)
{
	t_map	*map;
	int		fd;
	char	*line;

	map = ft_init_map(path, argc, argv);
	if (!map)
		return (NULL);
	fd = open(path, O_RDONLY);
	line = gnl(fd);
	if (!line)
		return (ft_printf(ERR_EMPTY, path), NULL);
	if (ft_fill_map(fd, map, line))
		return (NULL);
	close(fd);
	return (map);
}
