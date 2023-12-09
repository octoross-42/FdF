/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:47:32 by octoross          #+#    #+#             */
/*   Updated: 2023/12/07 16:47:32 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	ft_x_no(t_wire *wire, t_map *map)
{
	return (wire->x);
}

double	ft_y_no(t_wire *wire, t_map *map)
{
	return (wire->y);
}

double	ft_x_undo_no(t_wire *wire, t_map *map)
{
	return (wire->x);
}

double	ft_y_undo_no(t_wire *wire, t_map *map)
{
	return (wire->y);
}
