/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:43:29 by octoross          #+#    #+#             */
/*   Updated: 2023/12/06 17:43:29 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "fdf.h"
#include "constantes.h"

int	ft_min(int a, int b)
{
	if (a <= b)
		return (a);
	return (b);
}

int	ft_max(int a, int b)
{
	if (a >= b)
		return (a);
	return (b);
}

int	ft_color_of(int z, t_map *map)
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
	if (z >= 0)
	{
		r = z * (MAX_COLOR_R - 255) / map->max_altitude + 255;
		g = z * (MAX_COLOR_G - 255) / map->max_altitude + 255;
		b = z * (MAX_COLOR_B - 255) / map->max_altitude + 255;
	}
	else
	{
		r = z * (MIN_COLOR_R - 255) / map->min_altitude + 255;
		g = z * (MIN_COLOR_G - 255) / map->min_altitude + 255;
		b = z * (MIN_COLOR_B - 255) / map->min_altitude + 255;
	}
	return ((r << 16) | (g << 8) | b);
}

void	ft_clear_leftovers(t_gnl **leftovers)
{
	t_gnl	*next;
	t_gnl	*to_free;

	if (!(*leftovers))
		return ;
	next = *leftovers;
	while (next)
	{
		if (next->content)
			free(next->content);
		to_free = next;
		next = next->next;
		free(to_free);
	}
}

void	ft_clean_and_next_lst(t_gnl **line)
{
	t_gnl	*to_free;

	if ((*line)->start >= (*line)->len)
	{
		to_free = *line;
		*line = (*line)->next;
		free(to_free->content);
		free(to_free);
	}
}
