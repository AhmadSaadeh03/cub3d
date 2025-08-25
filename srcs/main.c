/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 18:56:44 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/25 13:02:27 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	finish_game(t_parsing *parsing, t_vars *vars, t_directions *directions,
		t_colors *colors)
{
	free_parsing(parsing);
	free_directions(directions);
	free_vars(vars);
	if (colors)
		free(colors);
	exit(0);
}

int	valid_extension(char **argv)
{
	char	*name;
	int		len;

	name = argv[1];
	len = ft_strlen(name);
	if (name[len - 1] == 'b' && name[len - 2] == 'u' && name[len - 3] == 'c'
		&& name[len - 4] == '.' && ft_isalnum(name[len - 5]))
		return (1);
	return (0);
}

static int	is_map_line(t_parsing *parsing, int i)
{
	int	j;

	j = 0;
	while (parsing->file[i][j] && parsing->file[i][j] != '\n')
	{
		if (parsing->file[i][j] == '1' && is_this_map(parsing, i))
			return (1);
		j++;
	}
	return (0);
}

int	first_line(t_parsing *parsing)
{
	int	i;

	i = 0;
	while (parsing->file[i])
	{
		if (is_map_line(parsing, i))
			return (i);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_parsing		*parsing;
	t_directions	*directions;
	t_vars			*vars;

	if (argc != 2)
		return (1);
	if (!valid_extension(argv))
	{
		write(2, "Error\n the extension of the file is wrong", 42);
		return (1);
	}
	parsing = malloc(sizeof(t_parsing));
	if (!parsing)
		return (1);
	directions = malloc(sizeof(t_directions));
	if (!directions)
	{
		free(parsing);
		return (1);
	}
	if (!init_parsing_directions(parsing, directions, argv[1]))
		return (1);
	vars = init_map(parsing);
	if (!vars)
		free_all_and_exit(parsing, vars, directions);
	check_lines(parsing, vars, directions);
	check_walls(parsing, vars, directions);
	init_colors(parsing, vars, directions);
}
