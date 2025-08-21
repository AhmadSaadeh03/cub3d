/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran < maemran@student.42amman.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 17:31:14 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/21 18:52:04 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdlib.h>
#include "./mlx/mlx.h"

# define WIDTH   1000
# define HIGHT   800
# define MS      0.1
# define RS      0.1
# define TEX_SIZE 64

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

typedef struct s_cub3d
{
    t_directions    *dir;
    t_colors        *color;
    t_vars          *data;
}   t_cub3d;


#endif