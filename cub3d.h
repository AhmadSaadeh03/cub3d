/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 17:31:14 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/10 18:05:27 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

typedef struct  s_colors
{
    //range between 0 to 255
    int ceil[3];//int 0->R 1->G 2->B
    int floor[3];
}   t_colors;

typedef struct s_directions
{
    // after parse every texture check if the texture valid in the path
    // check it by using FDs if it valid in the path
    char    *north;
    char    *south;
    char    *east;
    char    *west;
}   t_directions;

typedef struct s_vars
{
    char    **map;
}   t_vars;

#endif