/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constantes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:57:41 by octoross          #+#    #+#             */
/*   Updated: 2023/12/06 16:57:41 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTES_H

# define CONSTANTES_H

# define M_PI 3.14159265358979323846

# define MAX_COLOR_R 255
# define MAX_COLOR_G 140
# define MAX_COLOR_B 0
# define MIN_COLOR_R 10
# define MIN_COLOR_G 175
# define MIN_COLOR_B 125
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 500
# define MAP_WIDTH 700
# define MAP_HEIGHT 400
# define CASE_WIDTH 10
# define CASE_HEIGHT 1
# define ROTATION_SCALE 2
# define TRANSLATION_SCALE 1
# define TRANSLATION_RESFRESH 0.1
# define ZOOM_SCALE 1.05
# define ERR_OPEN "Cannot open map : %s\n"
# define ERR_EMPTY "Map is empty : %s\n"
# define ERR_MALLOC "Error : malloc failed\n"
# define ERR_FORMAT "Bad format for map at : %s\nline %d, position %d\n"
# define ERR_MAP "Error :%s : line %d has a width of %d supposed to be %d\n"
# define ERR_NO_MAP "Error : No map\n"
# define ERR_ARGS "Error : Too many arguments\n"
# define ERR_MLX_INIT "Error : mlx could not init\n"
# define ERR_MLX_WIN "Error : mlx could not load window\n"
# define ERR_MLX_IMG "Error : mlx could not load image\n"

#endif