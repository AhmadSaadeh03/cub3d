/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran < maemran@student.42amman.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 20:16:15 by maemran           #+#    #+#             */
/*   Updated: 2025/08/22 22:36:41 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    free_textures(t_cub3d *g)
{
    int i;

    i = 0;
    while (i < 4)
    {
        free(g->tex[i]);
        i++;
    }
}

void    init_structs(t_cub3d *g)
{
    g->color = NULL;
    g->data = NULL;
    g->dir = NULL;
    g->rc = NULL;
    g->tex = NULL;
}

void    free_structs(t_cub3d *g)
{
    if (g->color)
        free(g->color);
    if (g->dir)
        free (g->dir);
    if (g->data)
        free(g->data);
    if (g->rc)
        free (g->rc);
    if (g->tex)
        free (g->tex);//
    free (g);
}

int init_textures(t_cub3d *g)
{
    int i;

    i = 0;
    while (i < 4)
    {
        g->tex[i] = malloc(sizeof(t_texture));
        if (!g->tex[i])
        {
            while (i >= 0)
            {
                i--;
                free (g->tex[i]);
            }
            free_structs(g);
            return (1);
        }
        i++;
    }
    return (0);
}

t_cub3d *prepare_before_ray_casting(t_cub3d *g, t_colors *colors, t_vars *data, t_directions *dir)
{
    g = malloc(sizeof(t_cub3d));
    if (!g)
        return (NULL);
    init_structs (g);
    g->rc = malloc(sizeof(t_ray_casting));
    if (!g->rc)
    {
        free(g);
        return (NULL);
    }
    g->tex = malloc(sizeof(t_texture *) * 4);
    if (!g->tex)
    {
        free_structs(g);
        return (NULL);
    }
    if (init_textures(g))
        return (NULL);
    g->data = data;
    g->color = colors;
    g->dir = dir;
    return (g);
}

void    destroy_mlx(t_cub3d *g)
{
    int i;

    i = 0;
    while (i < 4)
    {
        mlx_destroy_image(g->data->mlx, g->tex[i]->img);
        i++;
    }
    mlx_destroy_image(g->data->mlx, g->data->img_buffer);
    mlx_destroy_window(g->data->mlx, g->data->win);
    mlx_destroy_display(g->data->mlx);
    free (g->data->mlx);
}

void    exit_window(t_cub3d *g)
{
    destroy_mlx(g);
    free_map(g);
    free_textures(g);
    free_structs(g);
    exit(0);
}