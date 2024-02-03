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
#include "constantes.h"

void	ft_isometric(t_proj_wire *to, t_wire *from, t_wire center)
{
	double	x;
	double	y;

	x = from->x - center.x;
	y = from->y - center.y;
	to->x = sqrt(2) / 2 * (x - y) + center.x;
	to->y = sqrt(6) / 6 * (x + y - 2 * from->z) + center.y;
}

void	ft_undo_isometric(t_proj_wire *to, t_wire *from, t_wire center)
{
	double	x;
	double	y;

	x = from->x - center.x;
	y = from->y - center.y;
	to->x = sqrt(2) / 2 * (x + sqrt(3)
			* y) + from->z / 6 + center.x;
	to->y = sqrt(2) / 2 * (sqrt(3)
			* y - x) + from->z / 6 + center.y;
}

// double	ft_x_isometric(t_wire *wire, t_map *map)
// {
// 	return (sqrt(2) / 2 * (wire->x - wire->y + map->center.y - map->center.x)
// 		+ map->center.x);
// }

// double	ft_y_isometric(t_wire *wire, t_map *map)
// {
// 	return (sqrt(6) / 6 * (wire->x + wire->y - map->center.x - map->center.y
// 			- 2 * wire->z) + map->center.y);
// }

// double	ft_x_undo_isometric(t_wire *wire, t_map *map)
// {
// 	return (sqrt(2) / 2 * (wire->x - map->center.x + sqrt(3)
// 			* (wire->y - map->center.y)) + wire->z / 6 + map->center.x);
// }

// double	ft_y_undo_isometric(t_wire *wire, t_map *map)
// {
// 	return (sqrt(2) / 2 * (map->center.x - wire->x + sqrt(3)
// 			* (wire->y - map->center.y)) + wire->z / 6 + map->center.y);
// }
