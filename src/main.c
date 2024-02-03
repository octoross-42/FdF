/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:36:18 by octoross          #+#    #+#             */
/*   Updated: 2023/10/25 21:36:18 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "constantes.h"

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

int	main(int argc, char **argv)
{
	t_window	*window;
	t_map		*map;

	if (argc < 2)
		return (ft_printf(ERR_NO_MAP), 1);
	if (argc > 3)
		return (ft_printf(ERR_ARGS), 1);
	map = ft_get_map(argv[1], argc - 1, &argv[1]);
	if (!map)
		return (1);
	window = ft_init_window(map);
	if (!window)
		return (1);
	ft_init_display(window);
}
