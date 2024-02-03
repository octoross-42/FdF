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

void	ft_set_dimensions(t_map *map)
{
	t_wire	*wire1;
	t_wire	*wire2;
	t_wire	*wire3;
	t_wire	*wire4;

	wire1 = map->wires[0][0];
	wire2 = map->wires[0][map->j - 1];
	wire3 = map->wires[map->i - 1][0];
	wire4 = map->wires[map->i - 1][map->j - 1];
	if (map->num_proj == 1)
	{
		map->width = sqrt(2) / 2 * (wire2->x - wire2->y - wire3->x + wire3->y);
		map->height = sqrt(6) / 6 * (wire4->x + wire4->y - 2 * (wire4->z + wire1->z) - wire1->x - wire1->y);
	}
	else if (map->num_proj == 2)
	{
		map->width = wire2->x - wire1->x;
		map->height = wire3->y - wire1->y;
	}
	else if (map->num_proj == 3)
	{
		map->width = wire2->x - wire1->x;
		map->height = wire3->y - wire1->y;
	}
	else if (map->num_proj == 0)
	{
		map->width = wire2->x - wire1->x;
		map->height = wire3->y - wire1->y;
	}	
}