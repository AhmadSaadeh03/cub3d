/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran < maemran@student.42amman.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:29:35 by maemran           #+#    #+#             */
/*   Updated: 2025/08/23 17:32:21 by maemran          ###   ########.fr       */
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

void put_pixel(t_cub3d *g, int x, int y, int color)
{
    *(int*)(g->data->img_addr + 
        y * g->data->line_length + x* (g->data->bpp / 8)) = color;
}

int get_texture_pixel(t_texture *tex, int x, int y)
{
    if (x < 0 || x >= TEX_SIZE || y < 0 || y >= TEX_SIZE)
        return (0);
    return (*(int*)(tex->addr + y * tex->line_len + x * (tex->bpp/8)));
}

void    set_directions_values(t_cub3d *g)
{
    double angle;
    
    angle = 0.0;
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
    if (x < 0 || x >= g->data->map_width
        || y < 0 || y >= g->data->map_height)
        return (1);
    if (g->data->map[y][x] == '1')
        return 1;
    return (0);
}

/***** modify this code later by remove old_dx and old_cx variables */
void rotate_player(t_cub3d *g, double angle)
{
    double old_dx;
    double old_cx; 

    old_dx = g->rc->x_facing_dir;
    old_cx = g->rc->cx_plane;
    g->rc->x_facing_dir = g->rc->x_facing_dir * cos(angle) - g->rc->y_facing_dir * sin(angle);
    g->rc->y_facing_dir = old_dx * sin(angle) + g->rc->y_facing_dir * cos(angle);
    g->rc->cx_plane = g->rc->cx_plane * cos(angle) - g->rc->cy_plane * sin(angle);
    g->rc->cy_plane = old_cx * sin(angle) + g->rc->cy_plane * cos(angle);
}

void move_player(t_cub3d *g, double move_x, double move_y)
{
    double new_x; 
    double new_y;
    
    new_x = g->data->xp_pos + move_x;
    new_y = g->data->yp_pos + move_y;
    if (!check_map_cell(g, (int)new_x, (int)g->data->yp_pos))
        g->data->xp_pos = new_x;
    if (!check_map_cell(g, (int)g->data->xp_pos, (int)new_y))
        g->data->yp_pos = new_y;
}

void get_ceiling_color(t_cub3d *g)
{
    g->color->c_mix = (g->color->ceil[0] << 16)
        | (g->color->ceil[1] << 8) | g->color->ceil[2];
}

void get_floor_color(t_cub3d *g)
{
    g->color->f_mix = (g->color->floor[0] << 16)
        | (g->color->floor[1] << 8) | g->color->floor[2];
}

int key_press(int key, t_cub3d *g)
{
    if (key == XK_Escape)
        exit_window(g);
    if (key == XK_w)
        move_player(g, g->rc->x_facing_dir * MOVESPEED,
            g->rc->y_facing_dir * MOVESPEED);
    if (key == XK_s)
        move_player(g, -g->rc->x_facing_dir * MOVESPEED,
            -g->rc->y_facing_dir * MOVESPEED);
    if (key == XK_a)
        move_player(g, g->rc->y_facing_dir * MOVESPEED,
            -g->rc->x_facing_dir * MOVESPEED);
    if (key == XK_d)
        move_player(g, -g->rc->y_facing_dir * MOVESPEED,
            g->rc->x_facing_dir * MOVESPEED);
    if (key == XK_Left)
        rotate_player(g, -ROTATSPEED);
    if (key == XK_Right)
        rotate_player(g, ROTATSPEED);
    return (0);
}

void    first_intersections(t_cub3d *g)
{
    if (g->rc->ray_dx < 0) /*left*/ 
    {
        g->rc->step_x = -1;
        g->rc->side_x = (g->data->xp_pos - g->rc->map_x)
            * g->rc->delta_x;
    } 
    else
    {
        g->rc->step_x = 1;
        g->rc->side_x = (g->rc->map_x + 1 - g->data->xp_pos)
            * g->rc->delta_x;
    }
    if (g->rc->ray_dy < 0)
    {
        g->rc->step_y = -1;
        g->rc->side_y = (g->data->yp_pos - g->rc->map_y)
            * g->rc->delta_y;
    }
    else /*down*/
    {
        g->rc->step_y = 1;
        g->rc->side_y = (g->rc->map_y + 1 - g->data->yp_pos)
            * g->rc->delta_y;
    }
}

void    set_rc_values(t_cub3d *g, double camera_x)
{
    g->rc->ray_dx = g->rc->x_facing_dir + g->rc->cx_plane * camera_x;
    g->rc->ray_dy = g->rc->y_facing_dir + g->rc->cy_plane * camera_x;
    g->rc->delta_x = fabs(1 / g->rc->ray_dx);
    g->rc->delta_y = fabs(1 / g->rc->ray_dy);
    g->rc->map_x = (int)g->data->xp_pos;
    g->rc->map_y = (int)g->data->yp_pos;
}

void    dda_algorithm(t_cub3d *g)
{
    int hit;
    
    hit = 0;
    g->rc->side = 0;
    while (!hit) 
    {
        if (g->rc->side_x < g->rc->side_y)
        {
            g->rc->side_x += g->rc->delta_x;
            g->rc->map_x += g->rc->step_x;
            g->rc->side = 0;
        } 
        else
        {
            g->rc->side_y += g->rc->delta_y;
            g->rc->map_y += g->rc->step_y;
            g->rc->side = 1;
        }
        if (check_map_cell(g, g->rc->map_x, g->rc->map_y))
            hit = 1;
    }
}

void    find_distance(t_cub3d *g)
{    
    if (g->rc->side == 0)
        g->rc->dist = (g->rc->map_x - g->data->xp_pos
            + (1 - g->rc->step_x) / 2) / g->rc->ray_dx;
    else
        g->rc->dist = (g->rc->map_y - g->data->yp_pos
            + (1 - g->rc->step_y) / 2) / g->rc->ray_dy;
    g->rc->line_height = (int)(HIGHT / g->rc->dist);
    g->rc->start = -g->rc->line_height / 2 + HIGHT / 2;
    g->rc->end = g->rc->line_height / 2 + HIGHT / 2;
    if (g->rc->start < 0)
        g->rc->start = 0;
    if (g->rc->end >= HIGHT)
        g->rc->end = HIGHT - 1;
}

void    set_texture_index(t_cub3d *g)
{
    g->rc->tex_id = 0;
    if (g->rc->side == 0)
    {
        if (g->rc->ray_dx < 0)
            g->rc->tex_id = 3;
        else
            g->rc->tex_id = 2;
    }
    else
    {
        if (g->rc->ray_dy < 0)
            g->rc->tex_id = 0;
        else
            g->rc->tex_id = 1;
    }
}

void    texture_position(t_cub3d *g)
{
    double wall_x;
    
    if (g->rc->side == 0)
        wall_x = g->data->yp_pos + g->rc->dist * g->rc->ray_dy;
    else 
        wall_x = g->data->xp_pos + g->rc->dist * g->rc->ray_dx;
    wall_x -= floor(wall_x);
    g->rc->tex_x = (int)(wall_x * TEX_SIZE);
    if ((g->rc->side == 0 && g->rc->ray_dx > 0) 
        || (g->rc->side == 1 && g->rc->ray_dy < 0))
        g->rc->tex_x = TEX_SIZE - g->rc->tex_x - 1;
    g->rc->step = 1.0 * TEX_SIZE / g->rc->line_height;
    g->rc->tex_pos = (g->rc->start - HIGHT / 2
        + g->rc->line_height / 2) * g->rc->step;
}

void    draw_ceiling(t_cub3d *g, int screen_x)
{
    g->rc->i = 0;
    while (g->rc->i < g->rc->start)
    {
        put_pixel(g, screen_x, g->rc->i, g->color->c_mix);
        g->rc->i++;
    }
}

void    draw_walls(t_cub3d *g, int screen_x)
{
    int color;
    
    while (g->rc->i < g->rc->end)
    {
        g->rc->tex_y = (int)(g->rc->tex_pos) & (TEX_SIZE - 1);
        g->rc->tex_pos += g->rc->step;
        color = get_texture_pixel(g->tex[g->rc->tex_id], g->rc->tex_x, g->rc->tex_y);
        put_pixel(g, screen_x, g->rc->i, color);
        g->rc->i++;
    }
}

void    draw_floor(t_cub3d *g, int screen_x)
{
    while (g->rc->i < HIGHT) 
    {
        put_pixel(g, screen_x, g->rc->i, g->color->f_mix);
        g->rc->i++;
    }
}

void cast_ray(t_cub3d *g, int screen_x)
{
    double camera_x;
    
    camera_x = 2 * screen_x / (double)WIDTH - 1;
    set_rc_values(g, camera_x);
    first_intersections(g);
    dda_algorithm(g);
    find_distance(g);
    set_texture_index(g);
    texture_position(g);
    draw_ceiling(g, screen_x);
    draw_walls(g, screen_x);
    draw_floor(g, screen_x);   
}

int rendering(t_cub3d *g)
{
    int x = 0;
    
    while (x < WIDTH)
    {
        cast_ray(g, x);
        x++;
    }
    mlx_put_image_to_window(g->data->mlx, g->data->win, g->data->img_buffer, 0, 0);
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
    get_ceiling_color(g);
    get_floor_color (g);
    mlx_hook(g->data->win, 2, 1L<<0, key_press, g);

    mlx_loop_hook(g->data->mlx, rendering, g);
    mlx_loop(g->data->mlx);
    return (0);
}
