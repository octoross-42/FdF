/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:05:27 by octoross          #+#    #+#             */
/*   Updated: 2023/12/05 17:05:27 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "constantes.h"

void	ft_reset_event(t_map *map, int init)
{
	map->event.init = init;
	map->event.rx = 0;
	map->event.ry = 0;
	map->event.rz = 0;
	map->event.tx = 0;
	map->event.ty = 0;
	map->event.zoom = 0;
	map->event.zoom_z = 0;
	map->event.x = 0;
	map->event.y = 0;
}

void	ft_apply_operations(t_map *map, t_wire *wire)
{
	if (map->event.tx != 0)
		wire->x += map->event.tx;
	if (map->event.ty != 0)
		wire->y += map->event.ty;
	if (map->event.zoom != 0)
	{
		wire->x = map->event.x + (wire->x - map->event.x) * map->event.zoom;
		wire->y = map->event.y + (wire->y - map->event.y) * map->event.zoom;
	}
	if (map->event.zoom_z != 0)
		wire->z = wire->z * map->event.zoom_z;
}

void	ft_apply_event(t_map *map, t_wire *wire)
{
	if (map->event.init == 1 && !wire->has_color)
		wire->color = ft_color_of(wire->color, map);
	else if (map->event.init == 2)
	{
		wire->x = ((double)wire->j) / 2 * CASE_WIDTH;
		wire->y = ((double)wire->i) / 2 * CASE_WIDTH;
		wire->z = wire->altitude * CASE_HEIGHT;
	}
	else if (map->event.init == 3)
	{
		if (wire->altitude > 0)
			wire->density /= map->nbr_alt_pos;
		else if (wire->altitude < 0)
			wire->density /= map->nbr_alt_neg;
		if (wire->altitude != 0)
			wire->color = ft_density_of(wire->density, wire->altitude, map);
	}
	else if (map->event.init == 4)
		return ;
	ft_apply_operations(map, wire);
}
