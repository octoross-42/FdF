/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:05:27 by octoross          #+#    #+#             */
/*   Updated: 2023/12/05 17:05:27 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "vars.h"

void	ft_apply_event(t_map *map, t_wire *wire)
{
	if (map->event.init == 1 && !wire->hasColor)
		wire->color = ft_color_of(wire->color, map);
	else if (map->event.init == 2)
	{
		wire->x = ((double)wire->j) / 2 * CASE_WIDTH;
		wire->y = ((double)wire->i) / 2 * CASE_WIDTH;
		wire->z = wire->altitude * CASE_HEIGHT;
	}
	else if (map->event.init == 3)
	{
		if (wire->altitude > 0)
			wire->density /= map->nbr_alt_pos;
		else if (wire->altitude < 0)
			wire->density /= map->nbr_alt_neg;
		if (wire->altitude != 0)
			wire->color = ft_density_color_of(wire->density, wire->altitude, map);
	}
	else if (map->event.init == 4)
		return ;
	if (map->event.tx != 0)
		wire->x += map->event.tx;
	if (map->event.ty != 0)
		wire->y += map->event.ty;
	if (map->event.zoom != 0)
	{
		wire->x = map->event.x + (wire->x - map->event.x) * map->event.zoom;
		wire->y = map->event.y + (wire->y - map->event.y) * map->event.zoom;
	}
	if (map->event.zoom_z != 0)
		wire->z = wire->z * map->event.zoom_z;
}

int	ft_key_press(int keycode, t_window *window)
{
	if (keycode == XK_Escape)
		return (ft_bybye(window), 0);
	if (keycode == 114)
	{
		window->map->event.init = 2;
		window->map->event.zoom = window->map->zoom_init;
		window->map->event.zoom_z = window->map->zoom_init;
		window->map->event.tx = WINDOW_WIDTH / 2 - (double)window->map->center.j / 2 * CASE_WIDTH;
		window->map->event.ty = WINDOW_HEIGHT / 2 - (double)window->map->center.i / 2 * CASE_WIDTH;
	}
	else if (keycode == 104)
	{
		window->map->event.init = 3;
		ft_apply_density(window->map);
	}
	else if (keycode == 65364)
		window->map->event.zoom_z = pow(ZOOM_SCALE, -1);
	else if (keycode == 65362)
		window->map->event.zoom_z = ZOOM_SCALE;
	else if (keycode == 65363)
		window->map->event.zoom = ZOOM_SCALE;
	else if (keycode == 65361)
		window->map->event.zoom = pow(ZOOM_SCALE, -1);
	else if (keycode == 112)
		window->map->event.init = 4;
	else
		return (0);
	if (keycode == 65363 || keycode == 65361 || keycode == 114)
	{
		window->map->event.x = WINDOW_WIDTH / 2;
		window->map->event.y = WINDOW_HEIGHT / 2;
	}
	ft_draw(window);
}

int	ft_mouse_release(int button, int x, int y, t_window *window)
{
	if (button == 1)
		window->left_press = 0;
	else if (button == 3)
		window->right_press = 0;
}

int	ft_move_mouse(int x, int y, t_window *window)
{
	if (!window->left_press && !window->right_press)
		return (1);
	if (window->left_press)
	{
		window->map->event.tx = (x - window->mouse_x) * TRANSLATION_SCALE;
		window->map->event.ty = (y - window->mouse_y) * TRANSLATION_SCALE;
	}
	else if (window->right_press)
	{
		// TODO (bon courage à moi-même à demain des bisous ;))
		window->map->event.rx = (x - window->mouse_x) * ROTATION_SCALE;
		window->map->event.ry = (y - window->mouse_y) * ROTATION_SCALE;
		window->map->event.rz = (y - window->mouse_y) * ROTATION_SCALE;
	}
	window->mouse_x = x;
	window->mouse_y = y;
	ft_draw(window);
}

int	ft_click_mouse(int button, int x, int y, t_window *window)
{
	if (button == 5)
		window->map->event.zoom = pow(ZOOM_SCALE, -1);
	else if (button == 4)
		window->map->event.zoom = ZOOM_SCALE;
	if (button == 5 || button == 4)
		window->map->event.zoom_z = window->map->event.zoom;
	else if (button == 1)
		window->left_press = 1;
	else if (button == 3)
		window->right_press = 1;
	else if (button == 2)
	{
		window->map->event.init = 2;
		window->map->event.zoom = window->map->zoom_init;
		window->map->event.zoom_z = window->map->zoom_init;
		window->map->event.x = WINDOW_WIDTH / 2;
		window->map->event.y = WINDOW_HEIGHT / 2;
		window->map->event.tx = WINDOW_WIDTH / 2 - (double)window->map->center.j / 2 * CASE_WIDTH;
		window->map->event.ty = WINDOW_HEIGHT / 2 - (double)window->map->center.i / 2 * CASE_WIDTH;
	}
	if (1 <= button && button <= 5 && button != 2)
	{
		window->map->event.x = x;
		window->map->event.y = y;
	}
	if (button == 1 ||button == 3)
	{
		window->mouse_x = x;
		window->mouse_y = y;
	}
	if (1 <= button && button <= 5)
		ft_draw(window);
}
