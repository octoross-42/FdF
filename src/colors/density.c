/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   density.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:52:59 by octoross          #+#    #+#             */
/*   Updated: 2023/12/11 18:52:59 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "constantes.h"

int	ft_density_of(double density, double altitude, t_map *map)
{
	int	r;
	int	g;
	int	b;
	int	min;
	int	max;

	max = ft_max(0, map->max_altitude);
	min = ft_max(0, map->min_altitude);
	if (map->max_altitude == map->min_altitude)
		return ((255 << 16) | (255 << 8) | 255);
	if (altitude >= 0)
	{
		r = density * (MAX_COLOR_R - 255) + 255;
		g = density * (MAX_COLOR_G - 255) + 255;
		b = density * (MAX_COLOR_B - 255) + 255;
	}
	else
	{
		r = density * (MIN_COLOR_R - 255) + 255;
		g = density * (MIN_COLOR_G - 255) + 255;
		b = density * (MIN_COLOR_B - 255) + 255;
	}
	return ((r << 16) | (g << 8) | b);
}

void	ft_compare_altitudes(t_wire *one, t_wire *two)
{
	if (one->altitude <= two->altitude && one->altitude > 0)
		two->density ++;
	else if (one->altitude >= two->altitude && one->altitude < 0)
		two->density ++;
	if (two->altitude <= one->altitude && two->altitude > 0)
		one->density ++;
	else if (two->altitude >= one->altitude && two->altitude < 0)
		one->density ++;
}

void	ft_apply_density(t_map *map)
{
	int		k;
	int		l;
	t_wire	*one;
	t_wire	*two;

	k = 0;
	while (k < map->i * map->j)
	{
		l = k + 1;
		while (l < map->i * map->j)
		{
			one = map->wires[k / map->j][k % map->j];
			two = map->wires[l / map->j][l % map->j];
			if ((one->altitude > 0 && two->altitude > 0)
				|| (one->altitude < 0 && two->altitude < 0))
				ft_compare_altitudes(one, two);
			l ++;
		}
		k ++;
	}
}
