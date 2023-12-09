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

double	ft_x_parallel(t_wire *wire, t_map *map)
{
	return (wire->x);
}

double	ft_y_parallel(t_wire *wire, t_map *map)
{
	return (wire->y);
}

double	ft_x_undo_parallel(t_wire *wire, t_map *map)
{
	return (wire->x);
}

double	ft_y_undo_parallel(t_wire *wire, t_map *map)
{
	return (wire->y);
}
