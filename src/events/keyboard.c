/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:40:50 by octoross          #+#    #+#             */
/*   Updated: 2024/02/03 15:20:56 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "constantes.h"

int	ft_event_zoom(int keycode, t_window *window)
{
	if (keycode == 65364)
		window->map->event.zoom_z = pow(ZOOM_SCALE, -1);
	else if (keycode == 65362)
		window->map->event.zoom_z = ZOOM_SCALE;
	else if (keycode == 65363)
		window->map->event.zoom = ZOOM_SCALE;
	else if (keycode == 65361)
		window->map->event.zoom = pow(ZOOM_SCALE, -1);
	else
		return (0);
	return (1);
}

void	ft_event_reinit(t_window *window)
{
	window->map->event.init = 2;
	window->map->event.zoom = window->map->zoom_init;
	window->map->event.zoom_z = window->map->zoom_init;
	window->map->event.tx = WINDOW_WIDTH / 2
		- (double)window->map->center.j / 2 * CASE_WIDTH;
	window->map->event.ty = WINDOW_HEIGHT / 2
		- (double)window->map->center.i / 2 * CASE_WIDTH;
}

int	ft_key_press(int keycode, t_window *window)
{
	if (keycode == XK_Escape)
		return (ft_bybye(window), 0);
	if (keycode == 114)
		ft_event_reinit(window);
	else if (keycode == 104)
	{
		window->map->event.init = 3;
		ft_apply_density(window->map);
	}
	else if (keycode == 112)
		window->map->event.init = 4;
	else if (!ft_event_zoom(keycode, window))
		return (0);
	if (keycode == 65363 || keycode == 65361 || keycode == 114)
	{
		window->map->event.x = WINDOW_WIDTH / 2;
		window->map->event.y = WINDOW_HEIGHT / 2;
	}
	ft_draw(window);
}
