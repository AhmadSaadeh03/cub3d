/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceil.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:07:24 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/23 16:31:50 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*init_ceil_numbers(t_parsing *parsing, t_vars *vars,
		t_directions *directions)
{
	int		i;
	int		j;
	char	*line;
	int		count;

	i = 1;
	j = 0;
	count = ft_strlen(parsing->ceil);
	count -= 1;
	line = malloc(sizeof(char) * count + 1);
	if (!line)
		print_and_free(parsing, vars, directions, "Error\nmalloc error");
	while (parsing->ceil[i])
	{
		line[j] = parsing->ceil[i];
		i++;
		j++;
	}
	line[j] = '\0';
	return (line);
}

t_colors	*get_ceil_number(t_parsing *parsing, t_vars *vars,
		t_directions *directions)
{
	int			i;
	char		**string;
	char		*line;
	t_colors	*colors;

	i = 0;
	line = init_ceil_numbers(parsing, vars, directions);
	colors = malloc(sizeof(t_colors));
	if (!colors)
		free_all_and_exit_two(parsing, vars, directions, line);
	string = ft_split(line, ',');
	if (!string)
	{
		free(line);
		free(colors);
		free_all_and_exit(parsing, vars, directions);
	}
	colors->ceil[0] = ft_atoi(string[0]);
	colors->ceil[1] = ft_atoi(string[1]);
	colors->ceil[2] = ft_atoi(string[2]);
	free_string(string, i);
	free(line);
	get_floor_number(parsing, vars, directions, colors);
	check_valid_numbers(parsing, vars, directions, colors);
	return (colors);
}

void	assign_ceil(t_parsing *parsing, t_vars *vars, t_directions *directions,
		int count)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	parsing->ceil = malloc(sizeof(char) * (count + 1));
	if (!parsing->ceil)
		print_and_free(parsing, vars, directions, "Error\nmalloc error\n");
	while (parsing->file[parsing->ceil_line][j] && k < count)
	{
		if (parsing->file[parsing->ceil_line][j] != ' '
			&& parsing->file[parsing->ceil_line][j] != '\t')
		{
			parsing->ceil[k] = parsing->file[parsing->ceil_line][j];
			k++;
		}
		j++;
	}
	parsing->ceil[k] = '\0';
}

void	check_number_on_ceil(t_parsing *parsing, t_vars *vars,
		t_directions *directions)
{
	int	i;

	i = 0;
	while (parsing->file[parsing->ceil_line][i] != '\n'
		&& parsing->file[parsing->ceil_line][i]
		&& parsing->file[parsing->ceil_line][i] != 'C')
	{
		if ((parsing->file[parsing->ceil_line][i] != ' '
				&& parsing->file[parsing->ceil_line][i] != '\t'))
			print_and_free(parsing, vars, directions,
				"Error\nthere is somthing before ceil");
		i++;
	}
}

void	init_ceil(t_parsing *parsing, t_vars *vars, t_directions *directions)
{
	int	j;
	int	save_first;
	int	save_last;
	int	count;

	j = 0;
	set_ceil(parsing, vars, directions);
	check_space_in_ceil(parsing, vars, directions);
	save_first = parsing->first_ceil;
	save_last = parsing->last_ceil;
	count = 0;
	while (parsing->file[parsing->ceil_line][j]
		&& parsing->file[parsing->ceil_line][j] != '\n')
	{
		if (parsing->file[parsing->ceil_line][j] != ' '
			&& parsing->file[parsing->ceil_line][j] != '\t')
			count++;
		j++;
	}
	parsing->first_ceil = save_first;
	parsing->last_ceil = save_last;
	assign_ceil(parsing, vars, directions, count);
	init_floor(parsing, vars, directions);
	check_letter_on_ceil(parsing, vars, directions);
	check_number_on_ceil(parsing, vars, directions);
}
