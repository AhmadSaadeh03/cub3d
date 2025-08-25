/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:37:54 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/25 16:01:35 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	count_res_lines(char *line)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (line[j])
	{
		if ((line[j] == 'N' && line[j + 1] == 'O') || (line[j] == 'S' && line[j
					+ 1] == 'O'))
			count++;
		if ((line[j] == 'E' && line[j + 1] == 'A') || (line[j] == 'W' && line[j
					+ 1] == 'E'))
			count++;
		if (line[j] == 'F' || line[j] == 'C')
			count++;
		j++;
	}
	return (count);
}

static int	is_one_time(t_parsing *parsing)
{
	int	i;
	int	total_count;

	i = 0;
	total_count = 0;
	while (parsing->file[i])
	{
		total_count += count_res_lines(parsing->file[i]);
		i++;
	}
	return (total_count == 6);
}

void	set_directions(t_parsing *parsing, t_directions *directions)
{
	init_directions(directions);
	if (!is_one_time(parsing))
		exit_and_error(parsing, directions,
			"Error\nthere is more or less than 6 resources");
	if (!set_dir_path(parsing, &directions->north, "NO"))
		exit_and_error(parsing, directions, "Error\nuncorrect NO");
	if (!set_dir_path(parsing, &directions->south, "SO"))
		exit_and_error(parsing, directions, "Error\nuncorrect SO");
	if (!set_dir_path(parsing, &directions->east, "EA"))
		exit_and_error(parsing, directions, "Error\nuncorrect EA");
	if (!set_dir_path(parsing, &directions->west, "WE"))
		exit_and_error(parsing, directions, "Error\nuncorrect WE");
}
