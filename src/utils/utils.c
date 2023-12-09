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
#include "vars.h"

int	ft_color_of(double z, t_map *map)
{
	int	r;
	int	g;
	int	b;

	if (map->max_color == map->min_color)
		return ((255 << 16) | (255 << 8) | 255);
	r = (z - map->min_color) * (MAX_COLOR_R - MIN_COLOR_R)
		/ (map->max_color - map->min_color) + MIN_COLOR_R;
	g = (z - map->min_color) * (MAX_COLOR_G - MIN_COLOR_G)
		/ (map->max_color - map->min_color) + MIN_COLOR_G;
	b = (z - map->min_color) * (MAX_COLOR_B - MIN_COLOR_B)
		/ (map->max_color - map->min_color) + MIN_COLOR_B;
	return ((r << 16) | (g << 8) | b);
}

double	ft_module2(double x, double y)
{
	return (sqrt(x * x + y * y));
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
