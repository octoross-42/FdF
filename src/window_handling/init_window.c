/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:03:25 by octoross          #+#    #+#             */
/*   Updated: 2023/12/05 17:03:25 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "constantes.h"

t_img	*ft_init_image(t_window *window)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->width = WINDOW_WIDTH;
	img->height = WINDOW_HEIGHT;
	img->img = mlx_new_image(window->mlx, img->width, img->height);
	img->addr = mlx_get_data_addr(img->img, &(img->bpp),
			&(img->size_line), &(img->endian));
	return (img);
}

void	ft_init_img_position(t_map *map)
{
	// TODO equation pour que coef s'applique sur la projection et pas sur la map de base
	ft_set_dimensions(map);

	if (MAP_WIDTH / map->width < MAP_HEIGHT / map->height)
		map->zoom_init = MAP_WIDTH / map->width;
	else
		map->zoom_init = MAP_HEIGHT / map->height;
	map->event.zoom = map->zoom_init;
	map->event.zoom_z = map->zoom_init;
	map->event.tx = WINDOW_WIDTH / 2 - map->center.x;
	map->event.ty = WINDOW_HEIGHT / 2 - map->center.y;
	map->event.x = WINDOW_WIDTH / 2;
	map->event.y = WINDOW_HEIGHT / 2;
}

t_window	*ft_init_window(t_map *map)
{
	t_window	*window;

	window = (t_window *)malloc(sizeof(t_window));
	if (!window)
		return (printf(ERR_MALLOC), NULL);
	window->left_press = 0;
	window->right_press = 0;
	window->mouse_x = 0;
	window->mouse_y = 0;
	window->mlx = mlx_init();
	if (!window->mlx)
		return (free(window), printf(ERR_MLX_INIT), NULL);
	window->win = mlx_new_window(window->mlx,
			WINDOW_WIDTH, WINDOW_HEIGHT, "Fdf Octoross");
	if (!window->win)
	{
		mlx_destroy_display(window->mlx);
		free(window->win);
		return (free(window), printf(ERR_MLX_WIN), NULL);
	}
	window->img = ft_init_image(window);
	if (window->img == NULL)
	{
		mlx_destroy_display(window->mlx);
		free(window->win);
		mlx_destroy_window(window->mlx, window->win);
		return (free(window), printf(ERR_MLX_IMG), NULL);
	}
	return (window->map = map, window);
}

void	ft_init_display(t_window *window)
{
	ft_draw(window);
	mlx_key_hook(window->win, ft_key_press, window);
	mlx_mouse_hook(window->win, ft_click_mouse, window);
	mlx_hook(window->win, 17, 0, ft_bybye, window);
	mlx_hook(window->win, 6, (1L<<6), ft_move_mouse, window);
	mlx_hook(window->win, 5, (1L<<3), ft_mouse_release, window);
	// mlx_hook(window->win, 6, (1L<<10), ft_move_mouse, window);
	mlx_loop(window->mlx);
}

int	ft_bybye(t_window *window)
{
	mlx_destroy_image(window->mlx, window->img->img);
	free(window->img);
	mlx_destroy_window(window->mlx, window->win);
	mlx_destroy_display(window->mlx);
	free(window->mlx);
	ft_clear_map(window->map, window->map->i, window->map->j);
	free(window);
	exit(0);
}
