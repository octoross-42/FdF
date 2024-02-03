/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dimensions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:43:03 by octoross          #+#    #+#             */
/*   Updated: 2024/01/09 16:43:03 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_set_dim_iso(t_map *map, t_wire *wires[4])
{
	map->width = sqrt(2) / 2
		* (wires[1]->x - wires[1]->y - wires[2]->x + wires[2]->y);
	map->height = sqrt(6) / 6
		* (wires[3]->x + wires[3]->y - 2 * (wires[3]->z + wires[0]->z)
			- wires[0]->x - wires[0]->y);
}

void	ft_set_dimensions(t_map *map)
{
	t_wire	*wires[4];

	wires[0] = map->wires[0][0];
	wires[1] = map->wires[0][map->j - 1];
	wires[2] = map->wires[map->i - 1][0];
	wires[3] = map->wires[map->i - 1][map->j - 1];
	if (map->num_proj == 1)
		ft_set_dim_iso(map, wires);
	else if (map->num_proj == 2)
	{
		map->width = wires[1]->x - wires[0]->x;
		map->height = wires[2]->y - wires[0]->y;
	}
	else if (map->num_proj == 0)
	{
		map->width = wires[1]->x - wires[0]->x;
		map->height = wires[2]->y - wires[0]->y;
	}	
}
