/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 17:31:14 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/21 19:18:16 by asaadeh          ###   ########.fr       */
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
    char    facing_dir;
    double  xp_pos;
    double  yp_pos;
    int map_height;
    int map_width;
}   t_vars;

typedef struct s_parsing
{
    char **file;
    int first_ceil;
    int last_ceil;
    int ceil_line;
    char *ceil;
    int first_floor;
    int last_floor;
    int floor_line;
    char *floor;
    int last_line_map;
}   t_parsing;


void init_directions(t_directions *directions);
int set_dir_path(t_parsing *parsing, char **destination,char *str);
void free_file(char **file);
void free_directions(t_directions *directions);
void free_parsing(t_parsing *parsing);
void exit_and_error(t_parsing *parsing ,t_directions *directions,char *str);
void set_directions(t_parsing *parsing,t_directions *directions);


void check_elements(t_parsing *parsing,t_vars *vars,t_directions *directions);
void check_taps(t_parsing *parsing,t_vars *vars,t_directions *directions);
t_vars *init_map(t_parsing *parsing);
void check_walls(t_parsing *parsing,t_vars *vars,t_directions *directions);
int first_line(t_parsing *parsing);

void    init_parsing(t_parsing  *parsing);
void free_all_and_exit(t_parsing *parsing , t_vars *vars,t_directions *directions);



void init_ceil(t_parsing *parsing,t_vars *vars,t_directions *directions);
t_colors *get_ceil_number(t_parsing *parsing,t_vars *vars,t_directions *directions);
void	set_ceil(t_parsing *parsing, t_vars *vars, t_directions *directions);
int	get_ceil_line(t_parsing *parsing);
void	check_comma_in_ceil(t_parsing *parsing, t_vars *vars,t_directions *directions);


void init_floor(t_parsing *parsing,t_vars *vars,t_directions *directions);
void  get_floor_number(t_parsing *parsing,t_vars *vars,t_directions *directions,t_colors *colors);
void check_valid_numbers(t_parsing *parsing,t_vars *vars,t_directions *directions,t_colors *colors);
void print_map(t_vars *vars);
int is_this_map(t_parsing *parsing,int i);
int validate_map(t_vars *vars);
void restore_map(t_vars *vars);
void get_max_width(t_vars *vars);
int    init_parsing_directions(t_parsing *parsing,t_directions *directions,char *argv);
char  **read_file(char *file_name);
void init_colors(t_parsing *parsing,t_vars *vars,t_directions *directions);
void free_vars(t_vars *vars);
void	free_string(char **string, int i);
void	free_all_and_exit_two(t_parsing *parsing, t_vars *vars,t_directions *directions,char *line);
void	set_floor(t_parsing *parsing, t_vars *vars, t_directions *directions);
void	check_comma_in_floor(t_parsing *parsing, t_vars *vars,t_directions *directions);
void check_image_path(t_parsing *parsing,t_vars *vars,t_directions *directinos);
void print_and_free(t_parsing *parsing, t_vars *vars, t_directions *directions,char *str);
#endif