/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran < maemran@student.42amman.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:29:35 by maemran           #+#    #+#             */
/*   Updated: 2025/08/21 18:53:33 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_map(t_vars *g);
void    parsing_part(t_vars *data, t_directions *dir, t_colors *colors);

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
    t_cub3d *g;
    
    /*************************************/
    /********** PARSING PART ************/
    /***********************************/
    
    t_vars  *data = malloc(sizeof(t_vars));
    t_colors *colors = malloc(sizeof(t_colors));
    t_directions    *dir = malloc(sizeof(t_directions));

    parsing_part(data, dir, colors);
    /*********************************/
    
    g = malloc(sizeof(t_cub3d));
    g->data = data;
    g->color = colors;
    g->dir = dir;
    g->data->mlx = mlx_init();
    g->data->win = mlx_new_window(g->data->mlx, WIDTH, HIGHT, "CUB3D");
    g->data->img_buffer = mlx_new_image(g->data->mlx, WIDTH, HIGHT);
    g->data->img_addr = mlx_get_data_addr(g->data->img_buffer, &g->data->bpp, &g->data->line_length, &g->data->endian);
    
    
    mlx_loop(g->data->mlx);
    return (0);
}