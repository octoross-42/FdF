/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 19:43:38 by octoross          #+#    #+#             */
/*   Updated: 2023/12/05 19:43:38 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "vars.h"

void	ft_draw_line(t_window *window, t_proj_wire *a, t_proj_wire *b)
{
	int				i;
	double			segment_lenght;
	t_proj_wire		p;
	char			*pixel;

	i = 0;
	segment_lenght = sqrt((b->x - a->x) * (b->x - a->x) + (b->y - a->y) * (b->y - a->y));
	while (i <= (segment_lenght) && segment_lenght != 0)
	{
		p.x = ((b->x - a->x) * i / segment_lenght + a->x);
		p.y = ((b->y - a->y) * i / segment_lenght + a->y);
		p.color = ft_min(b->color, a->color);
		if (0 <= p.x && p.x < WINDOW_WIDTH && 0 <= p.y && p.y < WINDOW_HEIGHT)
		{
			pixel = window->img->addr
				+ ((int)p.y * window->img->size_line
					+ (int)p.x * (window->img->bpp / 8));
			*(int *)pixel = p.color;
		}
		i ++;
	}
}

t_proj_wire	*ft_proj_wire(t_wire *wire, t_map *map)
{
	t_proj_wire	*proj;

	proj = (t_proj_wire *)malloc(sizeof(t_proj_wire));
	if (!proj)
		return (NULL);
	ft_apply_event(map, wire);
	map->proj(proj, wire, map->center);
	proj->color = wire->color;
	return (proj);
}

void	ft_set_node(t_map *map, int i, int j, t_tmp_wires *tmp)
// TODO : ajouter des cas en cas de fail malloc des tmp->
{
	t_wire	***wires;

	wires = map->wires;
	if (i == 0 && j == 0)
		tmp->root = ft_proj_wire(wires[i][j], map);
	else
	{
		if (j > 0)
			tmp->root = tmp->right;
		else
			tmp->root = tmp->next_line[j];
	}
	if (i + 1 < map->i)
		tmp->next_line[j] = ft_proj_wire(wires[i + 1][j], map);
	if (j + 1 < map->j)
	{
		if (i == 0)
			tmp->right = ft_proj_wire(wires[i][j + 1], map);
		else
			tmp->right = tmp->next_line[j + 1];
	}
}

void	ft_draw_map(t_window *window, t_tmp_wires *tmp)
{
	int			i;
	int			j;

	ft_apply_event(window->map, &window->map->center);
	i = 0;
	while (i < window->map->i)
	{
		j = 0;
		while (j < window->map->j)
		{
			ft_set_node(window->map, i, j, tmp);
			if (i + 1 < window->map->i)
				ft_draw_line(window, tmp->root, tmp->next_line[j]);
			if (j + 1 < window->map->j)
				ft_draw_line(window, tmp->root, tmp->right);
			free(tmp->root);
			j ++;
		}
		i ++;
	}
}

void	ft_draw(t_window *window)
{
	t_tmp_wires	tmp;

	if (window->map->event.init == 1)
		ft_init_img_position(window->map);
	else
	{
		mlx_destroy_image(window->mlx, window->img->img);
		window->img->img = mlx_new_image(window->mlx,
				window->img->width, window->img->height);
	}
	tmp.next_line = (t_proj_wire **)
		malloc(sizeof(t_proj_wire *) * (window->map->j));
	if (!(tmp.next_line))
	// TODO changer le return pour indiquer s'il faut clean et error message
		return ;
	ft_draw_map(window, &tmp);
	free(tmp.next_line);
	window->map->event.init = 0;
	window->map->event.rx = 0;
	window->map->event.ry = 0;
	window->map->event.rz = 0;
	window->map->event.tx = 0;
	window->map->event.ty = 0;
	window->map->event.zoom = 0;
	window->map->event.zoom_z = 0;
	window->map->event.x = 0;
	window->map->event.y = 0;
	mlx_put_image_to_window(window->mlx, window->win, window->img->img, 0, 0);
}
