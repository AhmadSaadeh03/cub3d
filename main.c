/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran < maemran@student.42amman.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:29:35 by maemran           #+#    #+#             */
/*   Updated: 2025/08/22 22:50:00 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_map(t_vars *g);
void    parsing_part(t_vars *data, t_directions *dir, t_colors *colors);

void    load_texture(t_cub3d *g, int index, char *path)
{
    g->tex[index]->img = mlx_xpm_file_to_image(g->data->mlx, path,
        &g->tex[index]->line_len, &g->tex[index]->endian);
    g->tex[index]->addr = mlx_get_data_addr(g->tex[index]->img, &g->tex[index]->bpp,
        &g->tex[index]->line_len, &g->tex[index]->endian);
}

void    set_directions_values(t_cub3d *g)
{
    double angle;
    
    if (g->data->facing_dir == 'E')
        angle = 0;
    else if (g->data->facing_dir == 'N')
        angle = M_PI / 2;
    else if (g->data->facing_dir == 'W')
        angle = M_PI;
    else if (g->data->facing_dir == 'S')
        angle = (3 * M_PI) / 2;
    g->rc->x_facing_dir = cos(angle);
    g->rc->y_facing_dir = -sin(angle);
    g->rc->cx_plane = -g->rc->y_facing_dir * FOV_FACTOR;
    g->rc->cy_plane =  g->rc->x_facing_dir * FOV_FACTOR;
}

int     check_map_cell(t_cub3d *g, int x, int y)
{
    if (x < 0 || x >= g->data->map_width || y < 0 || y >= g->data->map_height)
        return (1);
    if (g->data->map[y][x] == '1')
        return 1;
    return (0);
}

void move_player(t_game *g, double move_x, double move_y)
{
    double new_x; 
    double new_y;
    
    new_x = g->vars.xp_pos + move_x;
    new_y = g->vars.yp_pos + move_y;
    if (!check_map_cell(g, (int)new_x, (int)g->vars.yp_pos))
        g->vars.xp_pos = new_x;
    if (!check_map_cell(g, (int)g->vars.xp_pos, (int)new_y))
        g->vars.yp_pos = new_y;
}

int key_press(int key, t_cub3d *g) 
{
    if (key == XK_Escape)
        exit_window(g);
    if (key == XK_w)
        move_player(g, g->dx * MS, g->dy * MS);
    if (key == XK_s)
        move_player(g, -g->dx * MS, -g->dy * MS);
    if (key == XK_a)
        move_player(g, g->dy * MS, -g->dx * MS);
    if (key == XK_d)
        move_player(g, -g->dy * MS, g->dx * MS);
    if (key == XK_Left)
        rotate_player(g, -RS);
    if (key == XK_Right)
        rotate_player(g, RS);
    return 0;
}

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
    g = NULL;
    g = prepare_before_ray_casting(g, colors, data, dir);
    if (!g)
    {
        ft_putstr_fd("Error\nMemory allocation failure\n", 2);
        return (1);
    }
    g->data->mlx = mlx_init();
    g->data->win = mlx_new_window(g->data->mlx, WIDTH, HIGHT, "CUB3D");
    g->data->img_buffer = mlx_new_image(g->data->mlx, WIDTH, HIGHT);
    g->data->img_addr = mlx_get_data_addr(g->data->img_buffer,
        &g->data->bpp, &g->data->line_length, &g->data->endian);
    set_directions_values(g);
    load_texture (g, 0, g->dir->north);
    load_texture (g, 1, g->dir->south);
    load_texture (g, 2, g->dir->east);
    load_texture (g, 3, g->dir->west);
    mlx_hook(g->data->win, 2, 1L<<0, key_press, g);

    
    mlx_loop(g->data->mlx);
    return (0);
}