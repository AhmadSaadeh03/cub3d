/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 14:04:59 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/21 19:26:34 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_valid_numbers(t_parsing *parsing, t_vars *vars,
		t_directions *directions, t_colors *colors)
{
	if (!(colors->ceil[0] >= 0 && colors->ceil[0] <= 255)
		|| !(colors->ceil[1] >= 0 && colors->ceil[1] <= 255)
		|| !(colors->ceil[2] >= 0 && colors->ceil[2] <= 255))
	{
		write(2,"Error\ninvalid numbers in ceil line",35);
		free(colors);
		free_all_and_exit(parsing, vars, directions);
	}
	if (!(colors->floor[0] >= 0 && colors->floor[0] <= 255)
		|| !(colors->floor[1] >= 0 && colors->floor[1] <= 255)
		|| !(colors->floor[2] >= 0 && colors->floor[2] <= 255))
	{
		write(2,"Error\ninvalid numbers in floor line",36);
		free(colors);
		free_all_and_exit(parsing, vars, directions);
	}
}
