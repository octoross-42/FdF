/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:47:28 by octoross          #+#    #+#             */
/*   Updated: 2023/12/07 16:47:28 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_parallel(t_proj_wire *to, t_wire *from, t_wire center)
{
	double	x;
	double	y;

	x = from->x - center.x;
	y = from->y - center.y;
	to->x = sqrt(2) / 2 * (x - y) + center.x;
	to->y = sqrt(6) / 6 * (x + y - 2 * from->z) + center.y;
}

void	ft_undo_parallel(t_proj_wire *to, t_wire *from, t_wire center)
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

// double	ft_x_parallel(t_wire *wire, t_map *map)
// {
// 	return (wire->x);
// }

// double	ft_y_parallel(t_wire *wire, t_map *map)
// {
// 	return (wire->y);
// }

// double	ft_x_undo_parallel(t_wire *wire, t_map *map)
// {
// 	return (wire->x);
// }

// double	ft_y_undo_parallel(t_wire *wire, t_map *map)
// {
// 	return (wire->y);
// }
