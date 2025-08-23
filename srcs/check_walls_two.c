/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:04:00 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/23 16:32:27 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_row_start(t_parsing *parsing, t_vars *vars,
		t_directions *directions)
{
	int		i;
	int		j;
	char	first_char;

	i = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j] != '\n' && vars->map[i][j])
		{
			if (vars->map[i][j] != ' ' && vars->map[i][j] != '\t')
			{
				first_char = vars->map[i][j];
				if (first_char != '1')
				{
					printf("Error\nnot surrounded by walls (first index)\n");
					free_all_and_exit(parsing, vars, directions);
				}
				break ;
			}
			j++;
		}
		i++;
	}
}

static void	check_row_end(t_parsing *parsing, t_vars *vars,
		t_directions *directions)
{
	int		i;
	int		j;
	char	last_char;

	i = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j] != '\n' && vars->map[i][j])
			j++;
		j--;
		while (j >= 0 && (vars->map[i][j] == ' ' || vars->map[i][j] == '\t'))
			j--;
		if (j >= 0)
		{
			last_char = vars->map[i][j];
			if (last_char != '1')
			{
				printf("Error\nnot surrounded by walls (last index)\n");
				free_all_and_exit(parsing, vars, directions);
			}
		}
		i++;
	}
}

void	check_walls_two(t_parsing *parsing, t_vars *vars,
		t_directions *directions)
{
	check_row_start(parsing, vars, directions);
	check_row_end(parsing, vars, directions);
}
