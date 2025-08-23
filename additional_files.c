/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_files.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran < maemran@student.42amman.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:16:04 by maemran           #+#    #+#             */
/*   Updated: 2025/08/23 17:26:41 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *sample_map[] = {
    "1111111111111111111",
    "100000000001111111",
    "1001000000000111111", 
    "10000000000001",
    "1000000000000000000001", // Player facing North
    "10111001",
    "1N1 100001",
    "111 1111",
    NULL
};

void init_map(t_vars *g) 
{
    /////
    g->map_height = 0;
    while (sample_map[g->map_height]) 
        g->map_height++;
    
    // Find the maximum width across all rows
    g->map_width = 0;
    int i = 0;
    while (i < g->map_height) {
        int len = strlen(sample_map[i]);
        if (len > g->map_width) 
            g->map_width = len;
        i++;
    }
    //////


    
    g->map = malloc(g->map_height * sizeof(char*));
    int y = 0;
    while (y < g->map_height)
    {
        g->map[y] = malloc(g->map_width + 1);
        
        // Copy the row and pad with '1' if necessary
        strcpy(g->map[y], sample_map[y]);
        int current_len = strlen(sample_map[y]);
        while (current_len < g->map_width)
        {
            g->map[y][current_len] = '1';
            current_len++;
        }
        g->map[y][g->map_width] = '\0';
    
        int x = 0;
        while (x < g->map_width) {
            char c = g->map[y][x];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W') {
                g->xp_pos = x + 0.5;//x + 0.5;
                g->yp_pos = y + 0.5;//y + 0.5;
                g->facing_dir = c;
                g->map[y][x] = '0';
            }
            x++;
        }
        y++;
    }
}


void    parsing_part(t_vars *data, t_directions *dir, t_colors *colors)
{
    init_map(data);
    colors->ceil[0] = 135; // Sky blue
    colors->ceil[1] = 206;
    colors->ceil[2] = 235;
    
    colors->floor[0] = 68; // Dark gray
    colors->floor[1] = 68;
    colors->floor[2] = 68;

    dir->north = "./textures/eagle.xpm";
    dir->south = "./textures/mossy.xpm";  
    dir->east = "./textures/greystone.xpm";
    dir->west = "./textures/wood.xpm";
}

void    free_map(t_cub3d *g)
{
    int i;

    i = 0;
    while (g->data->map[i])
    {
        free(g->data->map[i]);
        i++;
    }
    free(g->data->map);
}