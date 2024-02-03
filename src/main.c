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

int	main(int argc, char **argv)
{
	t_window	*window;
	t_map		*map;
	int			fd;

	if (argc < 2)
		return (printf(ERR_NO_MAP), 1);
	if (argc > 3)
		return (printf(ERR_ARGS), 1);
	map = ft_get_map(argv[1], argc - 1, &argv[1]);
	if (!map)
		return (1);
	window = ft_init_window(map);
	if (!window)
		return (1);
	ft_init_display(window);
}
