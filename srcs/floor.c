/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:16:11 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/23 16:34:54 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*init_floor_numbers(t_parsing *parsing, t_vars *vars,
		t_directions *directions)
{
	int		i;
	int		j;
	char	*line;
	int		count;

	(void)vars;
	(void)directions;
	i = 1;
	j = 0;
	count = ft_strlen(parsing->floor);
	count -= 1;
	line = malloc(sizeof(char) * count + 1);
	if (!line)
	{
		write(2, "Error\nmalloc error", 19);
		return (NULL);
	}
	while (parsing->floor[i])
	{
		line[j] = parsing->floor[i];
		i++;
		j++;
	}
	line[j] = '\0';
	return (line);
}

void	get_floor_number(t_parsing *parsing, t_vars *vars,
		t_directions *directions, t_colors *colors)
{
	int		i;
	char	**string;
	char	*line;

	i = 0;
	line = init_floor_numbers(parsing, vars, directions);
	if (!line)
	{
		free(colors);
		free_all_and_exit(parsing, vars, directions);
	}
	string = ft_split(line, ',');
	if (!string)
	{
		free(line);
		free(colors);
		free_all_and_exit(parsing, vars, directions);
	}
	colors->floor[0] = ft_atoi(string[0]);
	colors->floor[1] = ft_atoi(string[1]);
	colors->floor[2] = ft_atoi(string[2]);
	free_string(string, i);
	free(line);
}

void	check_number_on_floor(t_parsing *parsing, t_vars *vars,
		t_directions *directions)
{
	int	i;

	i = 0;
	while (parsing->file[parsing->floor_line][i] != '\n'
		&& parsing->file[parsing->floor_line][i]
		&& parsing->file[parsing->floor_line][i] != 'F')
	{
		if ((parsing->file[parsing->floor_line][i] != ' '
				&& parsing->file[parsing->floor_line][i] != '\t'))
			print_and_free(parsing, vars, directions,
				"Error\nthere is somthing before floor");
		i++;
	}
}

void	assign_floor(t_parsing *parsing, t_vars *vars, t_directions *directions,
		int count)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	parsing->floor = malloc(sizeof(char) * (count + 1));
	if (!parsing->floor)
		print_and_free(parsing, vars, directions, "Error\nmalloc error");
	while (parsing->file[parsing->floor_line][j] && k < count)
	{
		if (parsing->file[parsing->floor_line][j] != ' '
			&& parsing->file[parsing->floor_line][j] != '\t')
		{
			parsing->floor[k] = parsing->file[parsing->floor_line][j];
			k++;
		}
		j++;
	}
	parsing->floor[k] = '\0';
}

void	init_floor(t_parsing *parsing, t_vars *vars, t_directions *directions)
{
	int	j;
	int	save_first;
	int	save_last;
	int	count;

	set_floor(parsing, vars, directions);
	check_space_in_floor(parsing, vars, directions);
	save_first = parsing->first_floor;
	save_last = parsing->last_floor;
	count = 0;
	j = 0;
	while (parsing->file[parsing->floor_line][j]
		&& parsing->file[parsing->floor_line][j] != '\n')
	{
		if (parsing->file[parsing->floor_line][j] != ' '
			&& parsing->file[parsing->floor_line][j] != '\t')
			count++;
		j++;
	}
	parsing->first_floor = save_first;
	parsing->last_floor = save_last;
	assign_floor(parsing, vars, directions, count);
	check_letter_on_floor(parsing, vars, directions);
	check_number_on_floor(parsing, vars, directions);
	check_comma_in_floor(parsing, vars, directions);
}
