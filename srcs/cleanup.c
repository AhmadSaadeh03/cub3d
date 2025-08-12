/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 16:28:13 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/12 16:28:43 by asaadeh          ###   ########.fr       */
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
void free_directions(t_directions *directions)
{
    if (directions->east)
        free(directions->east);
    if (directions->north)
        free(directions->north);
    if (directions->south)
        free(directions->south);
    if (directions->west)
        free(directions->west);
    if (directions)
        free(directions);
}
void free_parsing(t_parsing *parsing)
{
    if (parsing->file)
        free_file(parsing->file);
    if (parsing)
        free(parsing);
}

void exit_and_error(t_parsing *parsing ,t_directions *directions,char *str)
{
    free_parsing(parsing);
    free_directions(directions);
    printf("Error\n%s",str);
    exit (1);
}