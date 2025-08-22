/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran < maemran@student.42amman.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 17:31:14 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/22 22:50:04 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdlib.h>
#include "./mlx/mlx.h"
#include "./libft/libft.h"
#include <X11/keysym.h>
#include <math.h>

# define WIDTH      1000
# define HIGHT      600
# define FOV_FACTOR 0.7071
# define MS         0.1
# define RS         0.1
# define TEX_SIZE   64

typedef struct  s_colors
{
    int     ceil[3];
    int     floor[3];
}   t_colors;

typedef struct s_directions
{
    // after parse every texture check if the texture valid in the path
    // check it by using FDs if it valid in the path
    char    *north;
    char    *south;
    char    *east;
    char    *west;
}   t_directions;

typedef struct s_vars
{
    char    **map;
    void    *mlx;
    void    *win;
    void    *img_buffer;
    char    *img_addr;
    int     bpp;
    int     line_length;
    int     endian;
    char    facing_dir;
    double  xp_pos;
    double  yp_pos;
    int     map_height;
    int     map_width;
}   t_vars;

typedef struct s_ray_casting
{
    double cx_plane;
    double cy_plane;
    double x_facing_dir;
    double y_facing_dir;
}   t_ray_casting;

typedef struct s_texture
{
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
}   t_texture;


typedef struct s_cub3d
{
    t_directions    *dir;
    t_colors        *color;
    t_vars          *data;
    t_ray_casting   *rc;
    t_texture       **tex;
}   t_cub3d;

void    init_structs(t_cub3d *g);
void    free_structs(t_cub3d *g);
int     init_textures(t_cub3d *g);
void    free_textures(t_cub3d *g);
void    free_map(t_cub3d *g);
void    destroy_mlx(t_cub3d *g);
void    exit_window(t_cub3d *g);
t_cub3d     *prepare_before_ray_casting(t_cub3d *g, t_colors *colors, t_vars *data, t_directions *dir);
#endif