/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:37:54 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/23 18:46:58 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_after_path(int i, int check, t_parsing *parsing)
{
	while (parsing->file[i][check] != '\n' && parsing->file[i][check])
	{
		if ((parsing->file[i][check] != ' ' && parsing->file[i][check] != '\t'))
			return (0);
		check++;
	}
	return (1);
}

int	check_before_dir(int i, int j, t_parsing *parsing)
{
	if (j == 0)
		return (1);
	j--;
	while (j >= 0)
	{
		if (parsing->file[i][j] != ' ' && parsing->file[i][j] != '\t')
			return (0);
		j--;
	}
	return (1);
}

int	set_dir_path(t_parsing *parsing, char **destination, char *str)
{
	int	i;
	int	j;
	int	start;
	int	end;
	int	k;
	int	found;
	int	check;

	i = 0;
	j = 0;
	start = 0;
	end = 0;
	k = 0;
	found = 0;
	check = 0;
	while (parsing->file[i])
	{
		j = 0;
		while (parsing->file[i][j])
		{
			if (parsing->file[i][j] == '1' && is_this_map(parsing, i))
				return (0);
			if (parsing->file[i][j] == str[0] && parsing->file[i][j
				+ 1] == str[1])
			{
				if (!check_before_dir(i, j, parsing))
					return (0);
				j += 2;
				while (parsing->file[i][j] == ' '
					|| parsing->file[i][j] == '\t')
					j++;
				if (parsing->file[i][j] != '.')
					return (0);
				if (parsing->file[i][j + 1] != '/' && parsing->file[i][j
					+ 1] != '.')
					return (0);
				start = j;
				while ((parsing->file[i][j] && parsing->file[i][j] != '\n')
					&& (parsing->file[i][j] != ' '
						&& parsing->file[i][j] != '\t'))
					j++;
				end = j;
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
	check = j;
	if (!check_after_path(i, check, parsing))
		return (0);
	*destination = malloc(end - start + 1);
	if (!*destination)
		return (0);
	k = 0;
	while (start < end)
		(*destination)[k++] = parsing->file[i][start++];
	(*destination)[k] = '\0';
	return (1);
}
int	is_one_time(t_parsing *parsing)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (parsing->file[i])
	{
		j = 0;
		while (parsing->file[i][j])
		{
			if ((parsing->file[i][j] == 'N' && parsing->file[i][j + 1] == 'O')
				|| (parsing->file[i][j] == 'S' && parsing->file[i][j
					+ 1] == 'O'))
				count++;
			if ((parsing->file[i][j] == 'E' && parsing->file[i][j + 1] == 'A')
				|| (parsing->file[i][j] == 'W' && parsing->file[i][j
					+ 1] == 'E'))
				count++;
			if ((parsing->file[i][j] == 'F' || parsing->file[i][j] == 'C'))
				count++;
			j++;
		}
		i++;
	}
	if (count != 6)
		return (0);
	return (1);
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