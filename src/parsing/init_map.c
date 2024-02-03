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
#include "constantes.h"

t_wire	*ft_wire(int i, int j, t_altitude altitude)
{
	t_wire	*wire;

	wire = (t_wire *)malloc(sizeof(t_wire));
	if (!wire)
		return (ft_printf(ERR_MALLOC), NULL);
	wire->x = (double)j * CASE_WIDTH;
	wire->y = (double)i * CASE_WIDTH;
	wire->z = altitude.z * CASE_HEIGHT;
	wire->altitude = altitude.z;
	wire->i = 2 * i;
	wire->j = 2 * j;
	wire->has_color = altitude.has_color;
	if (altitude.has_color)
		wire->color = altitude.color;
	else
		wire->color = altitude.z;
	wire->density = 1;
	return (wire);
}

void	ft_set_projection(int argc, char **argv, t_map *map)
{
	if (argc == 1 || !strcmp(argv[1], "isometric"))
	{
		map->proj = ft_isometric;
		map->num_proj = 1;
	}
	else if (argc == 2 && !strcmp(argv[1], "parallel"))
	{
		map->proj = ft_parallel;
		map->num_proj = 2;
	}
	else if (argc == 2 && !strcmp(argv[1], "no"))
	{
		map->proj = ft_no;
		map->num_proj = 0;
	}
}

void	ft_init_center(t_map *map)
{
	map->center.x = ((double)map-> j - 1) / 2 * CASE_WIDTH;
	map->center.y = ((double)map-> i - 1) / 2 * CASE_WIDTH;
	map->center.i = map->i - 1;
	map->center.j = map->j - 1;
	map->center.z = 0;
	map->center.altitude = 0;
	map->center.density = 1;
	map->center.color = 0;
	map->center.has_color = 1;
}

t_map	*ft_init_map(char *path, int argc, char **argv)
{
	t_map		*map;
	int			fd;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->num_proj = -1;
	ft_set_projection(argc, argv, map);
	if (ft_map_dimension(&fd, path, map))
		return (free(map), NULL);
	ft_init_center(map);
	ft_reset_event(map, 1);
	map->nbr_alt_pos = 0;
	map->nbr_alt_neg = 0;
	map->sum_alt_pos = 0;
	map->sum_alt_neg = 0;
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
