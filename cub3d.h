/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 17:31:14 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/25 13:46:08 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "libft/libft.h"
# include "stdio.h"
# include <mlx.h>

typedef struct s_colors
{
	int			c_mix;
	int			f_mix;
	int			ceil[3];
	int			floor[3];
}			t_colors;

typedef struct s_directions
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
}			t_directions;

typedef struct s_vars
{
	char	**map;
	char	facing_dir;
	double	xp_pos;
	double	yp_pos;
	int		map_height;
	int		map_width;
}			t_vars;

typedef struct s_parsing
{
	char	**file;
	int		first_ceil;
	int		last_ceil;
	int		ceil_line;
	char	*ceil;
	int		first_floor;
	int		last_floor;
	int		floor_line;
	char	*floor;
	int		last_line_map;
}			t_parsing;

typedef struct s_path_info
{
	int		line_index;
	int		start;
	int		end;
	int		j;
}			t_path_info;

void		init_directions(t_directions *directions);
int			set_dir_path(t_parsing *parsing, char **destination, char *str);
void		free_file(char **file);
void		free_directions(t_directions *directions);
void		free_parsing(t_parsing *parsing);
void		exit_and_error(t_parsing *parsing, t_directions *directions,
				char *str);
void		set_directions(t_parsing *parsing, t_directions *directions);

void		check_elements(t_parsing *parsing, t_vars *vars,
				t_directions *directions);
void		check_taps(t_parsing *parsing, t_vars *vars,
				t_directions *directions);
t_vars		*init_map(t_parsing *parsing);
void		check_walls(t_parsing *parsing, t_vars *vars,
				t_directions *directions);
int			first_line(t_parsing *parsing);

void		init_parsing(t_parsing *parsing);
void		free_all_and_exit(t_parsing *parsing, t_vars *vars,
				t_directions *directions);

void		init_ceil(t_parsing *parsing, t_vars *vars,
				t_directions *directions);
t_colors	*get_ceil_number(t_parsing *parsing, t_vars *vars,
				t_directions *directions);
void		set_ceil(t_parsing *parsing, t_vars *vars,
				t_directions *directions);
int			get_ceil_line(t_parsing *parsing);
void		check_comma_in_ceil(t_parsing *parsing, t_vars *vars,
				t_directions *directions);

void		init_floor(t_parsing *parsing, t_vars *vars,
				t_directions *directions);
void		get_floor_number(t_parsing *parsing, t_vars *vars,
				t_directions *directions, t_colors *colors);
void		set_floor(t_parsing *parsing, t_vars *vars,
				t_directions *directions);
void		check_comma_in_floor(t_parsing *parsing, t_vars *vars,
				t_directions *directions);

void		check_valid_numbers(t_parsing *parsing, t_vars *vars,
				t_directions *directions, t_colors *colors);
int			is_this_map(t_parsing *parsing, int i);
int			validate_map(t_vars *vars);
void		restore_map(t_vars *vars);
void		get_max_width(t_vars *vars);
int			init_parsing_directions(t_parsing *parsing,
				t_directions *directions, char *argv);
char		**read_file(char *file_name);
void		init_colors(t_parsing *parsing, t_vars *vars,
				t_directions *directions);
void		free_vars(t_vars *vars);
void		free_string(char **string, int i);
void		free_all_and_exit_two(t_parsing *parsing, t_vars *vars,
				t_directions *directions, char *line);
void		check_image_path(t_parsing *parsing, t_vars *vars,
				t_directions *directinos);
void		print_and_free(t_parsing *parsing, t_vars *vars,
				t_directions *directions, char *str);
void		check_walls_two(t_parsing *parsing, t_vars *vars,
				t_directions *directions);
int			get_last_line(t_vars *vars, t_parsing *parsing);
void		check_space_in_ceil(t_parsing *parsing, t_vars *vars,
				t_directions *directions);
void		check_letter_on_ceil(t_parsing *parsing, t_vars *vars,
				t_directions *directions);
void		check_space_in_floor(t_parsing *parsing, t_vars *vars,
				t_directions *directions);
void		check_letter_on_floor(t_parsing *parsing, t_vars *vars,
				t_directions *directions);
void		check_taps(t_parsing *parsing, t_vars *vars, t_directions *dirs);
void		finish_game(t_parsing *parsing, t_vars *vars,
				t_directions *directions, t_colors *colors);
char		*init_floor_numbers(t_parsing *parsing, t_vars *vars,
				t_directions *directions);
char		*init_ceil_numbers(t_parsing *parsing, t_vars *vars,
				t_directions *directions);
char		**read_file(char *file_name);
void		check_lines(t_parsing *parsing, t_vars *vars,
				t_directions *directions);
int			match_identifier(char *line, int j, char *str);
int			check_before_dir(int i, int j, t_parsing *parsing);
int			check_after_path(int i, int check, t_parsing *parsing);
#endif
