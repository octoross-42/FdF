/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 14:40:40 by octoross          #+#    #+#             */
/*   Updated: 2024/02/03 15:27:06 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "constantes.h"

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

void	ft_mouse_reset(t_window *window)
{
	window->map->event.init = 2;
	window->map->event.zoom = window->map->zoom_init;
	window->map->event.zoom_z = window->map->zoom_init;
	window->map->event.x = WINDOW_WIDTH / 2;
	window->map->event.y = WINDOW_HEIGHT / 2;
	window->map->event.tx = WINDOW_WIDTH / 2
		- (double)window->map->center.j / 2 * CASE_WIDTH;
	window->map->event.ty = WINDOW_HEIGHT / 2
		- (double)window->map->center.i / 2 * CASE_WIDTH;
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
		ft_mouse_reset(window);
	if (1 <= button && button <= 5 && button != 2)
	{
		window->map->event.x = x;
		window->map->event.y = y;
	}
	if (button == 1 || button == 3)
	{
		window->mouse_x = x;
		window->mouse_y = y;
	}
	if (1 <= button && button <= 5)
		ft_draw(window);
}
