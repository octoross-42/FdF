/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_and_no.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:35:25 by octoross          #+#    #+#             */
/*   Updated: 2023/12/05 19:35:25 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "vars.h"

double	ft_x_isometric(t_wire *wire, t_map *map)
{
	return (sqrt(2) / 2 * (wire->x - wire->y + map->center.y - map->center.x)
		+ map->center.x);
}

double	ft_y_isometric(t_wire *wire, t_map *map)
{
	return (sqrt(6) / 6 * (wire->x + wire->y - map->center.x - map->center.y
			- 2 * wire->z) + map->center.y);
}

double	ft_x_undo_isometric(t_wire *wire, t_map *map)
{
	return (sqrt(2) / 2 * (wire->x - map->center.x + sqrt(3)
			* (wire->y - map->center.y)) + wire->z / 6 + map->center.x);
}

double	ft_y_undo_isometric(t_wire *wire, t_map *map)
{
	return (sqrt(2) / 2 * (map->center.x - wire->x + sqrt(3)
			* (wire->y - map->center.y)) + wire->z / 6 + map->center.y);
}
