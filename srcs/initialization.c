/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:04:28 by maemran           #+#    #+#             */
/*   Updated: 2025/08/25 16:14:34 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_structs(t_cub3d *g)
{
	g->color = NULL;
	g->data = NULL;
	g->dir = NULL;
	g->rc = NULL;
	g->tex = NULL;
}

int	init_textures(t_cub3d *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		g->tex[i] = malloc(sizeof(t_texture));
		if (!g->tex[i])
		{
			while (i >= 0)
			{
				i--;
				free(g->tex[i]);
			}
			free_structs(g);
			return (1);
		}
		i++;
	}
	return (0);
}

t_cub3d	*prepare_before_ray_casting(t_cub3d *g, t_colors *colors, t_vars *data,
		t_directions *dir)
{
	g = malloc(sizeof(t_cub3d));
	if (!g)
		return (NULL);
	init_structs(g);
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
