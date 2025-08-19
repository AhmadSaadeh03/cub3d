/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:28:13 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/19 17:30:08 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void free_file(char **file)
{
    int i = 0;
    if (!file)
        return;
    while (file[i])
        free(file[i++]);
    free(file);
}
void free_vars(t_vars *vars)
{
    int i = 0;
    if (vars)
    {
        if (vars->map)
        {
            while (vars->map[i])
            {
                free(vars->map[i]);
                i++;
            }
            free(vars->map);
        }
        free(vars);
    }
}
void free_directions(t_directions *directions)
{
    if (directions)
    {
        if (directions->east)
            free(directions->east);
        if (directions->north)
            free(directions->north);
        if (directions->south)
            free(directions->south);
        if (directions->west)
            free(directions->west);
        free(directions);
    }
}
void free_parsing(t_parsing *parsing)
{
    if (parsing)
    {
        if (parsing->file)
            free_file(parsing->file);
        if (parsing->ceil)
            free(parsing->ceil);
        if (parsing->floor)
            free(parsing->floor);
        free(parsing);
    }
}
void free_all_and_exit(t_parsing *parsing , t_vars *vars,t_directions *directions)
{
    free_parsing(parsing);
    free_directions(directions);
    free_vars(vars);
    exit(1);
}

void exit_and_error(t_parsing *parsing ,t_directions *directions,char *str)
{
    free_parsing(parsing);
    free_directions(directions);
    printf("Error\n%s",str);
    exit (1);
}
void	free_string(char **string, int i)
{
	while (string[i])
	{
		free(string[i]);
		i++;
	}
	free(string);
}

void	free_all_and_exit_two(t_parsing *parsing, t_vars *vars,
		t_directions *directions, char *line)
{
	free_parsing(parsing);
	free_directions(directions);
	free_vars(vars);
	if (line)
		free(line);
	exit(1);
}