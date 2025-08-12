/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 17:31:14 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/12 16:30:21 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H
# include "libft/libft.h"
# include <mlx.h>
# include "stdio.h"
typedef struct  s_colors
{
    //range between 0 to 255
    int ceil[3];//int 0->R 1->G 2->B
    int floor[3];
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
}   t_vars;

typedef struct s_parsing
{
    char **file;
    
}   t_parsing;


void init_directions(t_directions *directions);
int set_north(t_parsing *parsing,t_directions *directions);
int set_south(t_parsing *parsing,t_directions *directions);
int set_east(t_parsing *parsing,t_directions *directions);
int set_west(t_parsing *parsing,t_directions *directions);
int set_dir_path(t_parsing *parsing, char **destination,char *str);
void free_file(char **file);
void free_directions(t_directions *directions);
void free_parsing(t_parsing *parsing);
void exit_and_error(t_parsing *parsing ,t_directions *directions,char *str);
void set_directions(t_parsing *parsing,t_directions *directions);
#endif