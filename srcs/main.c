/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 18:56:44 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/23 16:30:29 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	count_lines(char *file_name)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (0);
	while ((line = get_next_line(fd)))
	{
		i++;
		free(line);
	}
	close(fd);
	return (i);
}

char	**read_file(char *file_name)
{
	char	*line;
	int		i;
	int		len;
	int		fd;
	char	**file;

	i = 0;
	len = count_lines(file_name);
	if (len <= 0)
		return (NULL);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (NULL);
	file = malloc(sizeof(char *) * (len + 1));
	if (!file)
	{
		write(2, "Error\nmalloc error", 19);
		return (NULL);
	}
	while ((line = get_next_line(fd)))
	{
		file[i] = line;
		i++;
	}
	file[i] = NULL;
	close(fd);
	return (file);
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

void	check_lines(t_parsing *parsing, t_vars *vars, t_directions *directions)
{
	int	i;
	int	j;
	int	not_empty;
	int	stop;

	i = 0;
	j = 0;
	not_empty = 0;
	stop = 0;
	while (parsing->file[i])
	{
		j = 0;
		while (parsing->file[i][j] && parsing->file[i][j] != '\n')
		{
			if (parsing->file[i][j] == '1' && is_this_map(parsing, i))
			{
				stop = 1;
				break ;
			}
			if (ft_isalnum(parsing->file[i][j]))
			{
				not_empty++;
				break ;
			}
			j++;
		}
		if (stop)
			break ;
		i++;
	}
	if (not_empty != 6)
	{
		write(2, "Error\nthe numbers of resources is wrong", 40);
		free_all_and_exit(parsing, vars, directions);
	}
	init_ceil(parsing, vars, directions);
	check_comma_in_ceil(parsing, vars, directions);
}
int	first_line(t_parsing *parsing)
{
	int	i;
	int	j;
	int	save_line;
	int	found;

	i = 0;
	j = 0;
	save_line = 0;
	found = 0;
	while (parsing->file[i])
	{
		j = 0;
		while (parsing->file[i][j] && parsing->file[i][j] != '\n')
		{
			if (parsing->file[i][j] == '1' && is_this_map(parsing, i))
			{
				save_line = i;
				found = 1;
				break ;
			}
			j++;
		}
		if (found)
			break ;
		i++;
	}
	if (!found)
		return (0);
	return (save_line);
	return (1);
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
	// check_image_path(parsing,vars,directions);
	check_lines(parsing, vars, directions);
	check_walls(parsing, vars, directions);
	// print_map(vars);
	init_colors(parsing, vars, directions);
	// invalid char and ../
}
