/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:20:17 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/16 16:24:09 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void init_directions(t_directions *directions)
{
    directions->east = NULL;
    directions->north = NULL;
    directions->south = NULL;
    directions->west = NULL;
}
void    init_parsing(t_parsing  *parsing)
{
    parsing->ceil = NULL;
    parsing->floor = NULL;
    parsing->file = NULL;
    parsing->ceil_line = -1;
    parsing->first_ceil = -1;
    parsing->first_floor = -1;
    parsing->floor_line = -1;
    parsing->last_ceil = -1;
    parsing->last_floor = -1;
}