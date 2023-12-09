/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:37:51 by octoross          #+#    #+#             */
/*   Updated: 2023/12/05 21:37:51 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "vars.h"

t_wire	*ft_wire(int i, int j, t_altitude altitude)
{
	t_wire	*wire;

	wire = (t_wire *)malloc(sizeof(t_wire));
	if (!wire)
		return (NULL);
	wire->x = (double)j * CASE_WIDTH;
	wire->y = (double)i * CASE_WIDTH;
	wire->z = altitude.z * CASE_HEIGHT;
	wire->altitude = altitude.z;
	wire->i = 2 * i;
	wire->j = 2 * j;
	wire->hasColor = altitude.hasColor;
	if (altitude.hasColor)
		wire->color = altitude.color;
	else
		wire->color = altitude.z;
	return (wire);
}

void	ft_clear_strs(char	**strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i ++]);
	free(strs);
}

void	ft_set_projection(int argc, char **argv, t_map *map)
{
	if (argc == 1 || !strcmp(argv[1], "isometric"))
	{
		map->proj_x = ft_x_isometric;
		map->proj_y = ft_y_isometric;
		map->num_proj = 1;
	}
	else if (argc == 2 && !strcmp(argv[1], "cubic"))
	{
		map->proj_x = ft_x_cubic;
		map->proj_y = ft_y_cubic;
		map->num_proj = 2;
	}
	else if (argc == 2 && !strcmp(argv[1], "parallel"))
	{
		map->proj_x = ft_x_parallel;
		map->proj_y = ft_y_parallel;
		map->num_proj = 3;
	}
	else if (argc == 2 && !strcmp(argv[1], "no"))
	{
		map->proj_x = ft_x_no;
		map->proj_y = ft_y_no;
		map->num_proj = 0;
	}
}

t_map	*ft_init_map(char *path, int argc, char **argv)
{
	t_map	*map;
	int		fd;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->num_proj = -1;
	ft_set_projection(argc, argv, map);
	if (ft_map_dimension(&fd, path, map) == 1)
		return (free(map), NULL);
	map->center.x = (map-> j - 1) / 2 * CASE_WIDTH;
	map->center.y = (map-> i - 1) / 2 * CASE_WIDTH;
	map->center.i = map->i - 1;
	map->center.j = map->j - 1;
	map->center.z = 0;
	map->center.altitude = 0;
	map->event.rx = 0;
	map->event.ry = 0;
	map->event.tx = 0;
	map->event.ty = 0;
	map->event.zoom = 0;
	map->event.x = 0;
	map->event.y = 0;
	map->event.init = 1;
	return (map);
}

void	ft_clear_map(t_map *map, int n, int m)
{
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = 0;
		if (i + 1 < n)
		{
			while (j < map->j)
				free(map->wires[i][j ++]);
		}
		else
		{
			while (j < m)
				free(map->wires[i][j ++]);
		}
		free(map->wires[i ++]);
	}
	free(map->wires);
	free(map);
}
