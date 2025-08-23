/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceil_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:23:40 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/23 16:33:48 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_space_in_ceil(t_parsing *parsing, t_vars *vars,
		t_directions *directions)
{
	int		j;
	int		in_number;
	char	c;
	int		k;

	j = 0;
	in_number = 0;
	while (parsing->file[parsing->ceil_line][j]
		&& parsing->file[parsing->ceil_line][j] != '\n')
	{
		c = parsing->file[parsing->ceil_line][j];
		if (ft_isdigit(c))
			in_number = 1;
		else if (c == ' ' || c == '\t')
		{
			if (in_number)
			{
				k = j + 1;
				while (parsing->file[parsing->ceil_line][k] == ' ')
					k++;
				if (ft_isdigit(parsing->file[parsing->ceil_line][k]))
					print_and_free(parsing, vars, directions,
						"Error\nspace inside the number field");
				in_number = 0;
			}
		}
		else if (c == ',')
			in_number = 0;
		j++;
	}
}
void	check_letter_on_ceil(t_parsing *parsing, t_vars *vars,
		t_directions *directions)
{
	int		i;
	int		count;
	char	c;

	i = 0;
	count = 0;
	while (parsing->file[parsing->ceil_line][i] != '\n'
		&& parsing->file[parsing->ceil_line][i])
	{
		if (ft_isalpha(parsing->file[parsing->ceil_line][i]))
		{
			c = parsing->file[parsing->ceil_line][i];
			count++;
		}
		i++;
	}
	if (count != 1 || c != 'C')
	{
		write(2, "Error\non ceil line", 19);
		free_all_and_exit(parsing, vars, directions);
	}
}
void	check_space_in_floor(t_parsing *parsing, t_vars *vars,
		t_directions *directions)
{
	int		j;
	int		in_number;
	char	c;
	int		k;

	j = 0;
	in_number = 0;
	while (parsing->file[parsing->floor_line][j]
		&& parsing->file[parsing->floor_line][j] != '\n')
	{
		c = parsing->file[parsing->floor_line][j];
		if (ft_isdigit(c))
			in_number = 1;
		else if (c == ' ' || c == '\t')
		{
			if (in_number)
			{
				k = j + 1;
				while (parsing->file[parsing->floor_line][k] == ' ')
					k++;
				if (ft_isdigit(parsing->file[parsing->floor_line][k]))
					print_and_free(parsing, vars, directions,
						"Error\nspace inside the number field");
				in_number = 0;
			}
		}
		else if (c == ',')
			in_number = 0;
		j++;
	}
}
void	check_letter_on_floor(t_parsing *parsing, t_vars *vars,
		t_directions *directions)
{
	int i;
	int count;
	char c;

	i = 0;
	count = 0;
	while (parsing->file[parsing->floor_line][i] != '\n'
		&& parsing->file[parsing->floor_line][i])
	{
		if (ft_isalpha(parsing->file[parsing->floor_line][i]))
		{
			c = parsing->file[parsing->floor_line][i];
			count++;
		}
		i++;
	}
	if (count != 1 || c != 'F')
	{
		write(2, "Error\nto many letters on floor line", 36);
		free_all_and_exit(parsing, vars, directions);
	}
}