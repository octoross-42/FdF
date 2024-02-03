/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 21:33:58 by octoross          #+#    #+#             */
/*   Updated: 2023/10/25 21:33:58 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H

# include "utils.h"
// TODO A REMPLACER printf et strcmp
# include <stdio.h>
# include <string.h>

# include <time.h>
# include <stddef.h>
# include <unistd.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>

# define M_PI 3.14159265358979323846

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
	// TODO enlever width et height
	int			width;
	int			height;
}				t_img;

typedef struct s_altitude
{
	int		isValid;
	double	z;
	int		color;
	int		hasColor;
}		t_altitude;

t_altitude	ft_read_altitude(char *word);

typedef struct s_wire
{
	double	x;
	double	y;
	double	z;
	double	altitude;
	int		i;
	int		j;
	int		color;
	double	density;
	// TODO contradiction avec double 
	// qui est accepte par le read de la map 
	int		hasColor;
}	t_wire;

t_wire	*ft_wire(int i, int j, t_altitude altitude);

// TODO fonction that does both to recipient from model (with tmp variables ofc)

typedef struct s_proj_wire
{
	double	x;
	double	y;
	int		color;
}	t_proj_wire;

typedef struct s_tmp_wires
{
	t_proj_wire	*root;
	t_proj_wire	*right;
	t_proj_wire	**next_line;
}	t_tmp_wires;

typedef struct s_event
{
	int		init;
	double	rx;
	double	ry;
	double	rz;
	double	tx;
	double	ty;
	double	zoom;
	double	zoom_z;
	int		x;
	int		y;
}	t_event;

typedef struct s_map
{
	t_wire	center;
	double	min_altitude;
	double	max_altitude;
	double	zoom_init;
	int	i;
	int	j;
	t_wire	***wires;
	int		num_proj;
	void	(*proj)(t_proj_wire *, t_wire *, t_wire center);
	double	sum_alt_pos;
	double	sum_alt_neg;
	double	nbr_alt_pos;
	double	nbr_alt_neg;
	double	width;
	double	height;
	clock_t t;
	t_event	event;
}	t_map;

void	ft_no(t_proj_wire *to, t_wire *from, t_wire center);
void	ft_set_dimensions(t_map *map);
void	ft_apply_event(t_map *map, t_wire *wire);
void	ft_isometric(t_proj_wire *to, t_wire *from, t_wire center);
void	ft_conic(t_proj_wire *to, t_wire *from, t_wire center);
void	ft_parallel(t_proj_wire *to, t_wire *from, t_wire center);

void	ft_undo_isometric(t_proj_wire *to, t_wire *from, t_wire center);
void	ft_undo_conic(t_proj_wire *to, t_wire *from, t_wire center);
void	ft_undo_parallel(t_proj_wire *to, t_wire *from, t_wire center);

double	ft_x_isometric(t_wire *wire, t_map *map);
double	ft_y_isometric(t_wire *wire, t_map *map);
double	ft_x_undo_isometric(t_wire *wire, t_map *map);
double	ft_y_undo_isometric(t_wire *wire, t_map *map);
double	ft_x_no(t_wire *wire, t_map *map);
double	ft_y_no(t_wire *wire, t_map *map);
double	ft_x_undo_no(t_wire *wire, t_map *map);
double	ft_y_undo_no(t_wire *wire, t_map *map);
double	ft_x_conic(t_wire *wire, t_map *map);
double	ft_y_conic(t_wire *wire, t_map *map);
double	ft_x_undo_conic(t_wire *wire, t_map *map);
double	ft_y_undo_conic(t_wire *wire, t_map *map);
double	ft_x_parallel(t_wire *wire, t_map *map);
double	ft_y_parallel(t_wire *wire, t_map *map);
double	ft_x_undo_parallel(t_wire *wire, t_map *map);
double	ft_y_undo_parallel(t_wire *wire, t_map *map);

void	ft_init_img_position(t_map *map);
int		ft_color_of(int z, t_map *map);
void	ft_apply_density(t_map *map);
int		ft_density_of(double density, double altitude, t_map *map);
void	ft_clear_strs(char	**strs);
void	ft_clear_map(t_map *map, int n, int m);
t_map	*ft_init_map(char *path, int argc, char **argv);
int		ft_map_dimension(int *fd, char *path, t_map	*map);
t_map	*ft_get_map(char *path, int argc, char **argv);

typedef struct s_window
{
    void	*mlx;
    void	*win;
	t_img	*img;
	t_map	*map;
	int		map_width;
	int		map_height;
	int		window_width;
	int		window_height;
	int		left_press;
	int		right_press;
	int		mouse_x;
	int		mouse_y;
}	t_window;

void	ft_draw(t_window *window);

int	ft_move_mouse(int x, int y, t_window *window);
int	ft_key_press(int keycode, t_window *window);
int	ft_mouse_release(int button, int x, int y, t_window *window);
int	ft_click_mouse(int button, int x, int y, t_window *window);

t_window	*ft_init_window(t_map *map);
void		ft_init_display(t_window *window);
int			ft_bybye(t_window *window);

#endif