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

void	ft_apply_event(t_event event, t_wire *wire)
{
	if (event.init == 2)
	{
		wire->x = wire->j / 2 * CASE_WIDTH;
		wire->y = wire->i / 2 * CASE_WIDTH;
		wire->z = wire->altitude * CASE_HEIGHT;
	}
	if (event.tx != 0)
		wire->x += event.tx;
	if (event.ty != 0)
		wire->y += event.ty;
	if (event.zoom != 0)
	{
		wire->x = event.x + (wire->x - event.x) * event.zoom;
		wire->y = event.y + (wire->y - event.y) * event.zoom;
		wire->z = wire->z * event.zoom;
	}
}

int	ft_key_press(int keycode, t_window *window)
{
	if (keycode == XK_Escape)
		ft_bybye(window);
}

int	ft_mouse_release(int button, int x, int y, t_window *window)
{
	if (button == 1)
		window->left_press = 0;
	else if (button == 3)
		window->right_press = 0;
	// printf("lalallaalla\n");
	// printf("key : %d\n", button);
}

int	ft_move_mouse(int x, int y, t_window *window)
{
	// if (window->left_press)
	// 	printf("translation : %d %d\n", x, y);
	// else if (window->right_press)
	// 	printf("rotation : %d %d\n", x, y);
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
	}
	window->mouse_x = x;
	window->mouse_y = y;
	ft_draw(window);
}

int	ft_click_mouse(int button, int x, int y, t_window *window)
{
	printf("x : %d, y : %d\n", x, y);
	if (button == 5)
	{
		window->map->event.zoom = pow(ZOOM_SCALE, -1);
		printf("UP\n");
	}
	else if (button == 4)
	{
		printf("DOWN\n");
		window->map->event.zoom = pow(ZOOM_SCALE, 1);
	}
	else if (button == 1)
	{
		window->left_press = 1;
		window->mouse_x = x;
		window->mouse_y = y;
		printf("Left\n");
	}
	else if (button == 3)
	{
		window->right_press = 1;
		window->mouse_x = x;
		window->mouse_y = y;
		printf("Right\n");
	}
	else if (button == 2)
	{
		window->map->event.init = 2;
		window->map->event.zoom = window->map->zoom_init;
		window->map->event.x = WINDOW_WIDTH / 2;
		window->map->event.y = WINDOW_HEIGHT / 2;
		window->map->event.tx = WINDOW_WIDTH / 2 - window->map->center.j / 2 * CASE_WIDTH;
		window->map->event.ty = WINDOW_HEIGHT / 2 - window->map->center.i / 2 * CASE_WIDTH;
		printf("Poink\n");
	}
	else
		printf("button : %d\n", button);
	if (1 <= button && button <= 5 && button != 2)
	{
		window->map->event.x = x;
		window->map->event.y = y;
	}
	if (1 <= button && button <= 5)
		ft_draw(window);
}
