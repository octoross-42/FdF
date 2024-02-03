/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conic_and_parrallel.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:35:02 by octoross          #+#    #+#             */
/*   Updated: 2023/12/05 19:35:02 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_conic(t_proj_wire *to, t_wire *from, t_wire center)
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

void	ft_undo_conic(t_proj_wire *to, t_wire *from, t_wire center)
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

double	ft_x_conic(t_wire *wire, t_map *map)
{
	return (wire->x);
}

double	ft_y_conic(t_wire *wire, t_map *map)
{
	return (wire->y);
}

double	ft_x_undo_conic(t_wire *wire, t_map *map)
{
	return (wire->x);
}

double	ft_y_undo_conic(t_wire *wire, t_map *map)
{
	return (wire->y);
}
