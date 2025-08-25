/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemran <maemran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:29:35 by maemran           #+#    #+#             */
/*   Updated: 2025/08/25 13:30:05 by maemran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rendering(t_cub3d *g)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		cast_ray(g, x);
		x++;
	}
	mlx_put_image_to_window(g->data->mlx, g->data->win, g->data->img_buffer, 0,
		0);
	return (0);
}

int	close_button(t_cub3d *g)
{
	exit_window(g);
	return (0);
}

int	mouse_move(int x, int y, t_cub3d *g)
{
	static int	last_x = WIDTH / 2;
	int			delta_x;

	(void)y;
	delta_x = x - last_x;
	if (delta_x > 0)
		rotate_player(g, ROTATSPEED / 4);
	else if (delta_x < 0)
		rotate_player(g, -ROTATSPEED / 4);
	last_x = x;
	return (0);
}

void	mlx_manage(t_cub3d *g)
{
	g->data->mlx = mlx_init();
	g->data->win = mlx_new_window(g->data->mlx, WIDTH, HIGHT, "CUB3D");
	g->data->img_buffer = mlx_new_image(g->data->mlx, WIDTH, HIGHT);
	g->data->img_addr = mlx_get_data_addr(g->data->img_buffer, &g->data->bpp,
			&g->data->line_length, &g->data->endian);
	set_directions_values(g);
	load_texture(g, 0, g->dir->north);
	load_texture(g, 1, g->dir->south);
	load_texture(g, 2, g->dir->east);
	load_texture(g, 3, g->dir->west);
	get_ceiling_color(g);
	get_floor_color(g);
	mlx_hook(g->data->win, 2, 1L << 0, key_press, g);
	mlx_hook(g->data->win, 17, 0, close_button, g);
	mlx_hook(g->data->win, 6, 1L << 6, mouse_move, g);
	mlx_loop_hook(g->data->mlx, rendering, g);
	mlx_loop(g->data->mlx);
}

// int magfgfdgdfin(int argc, char **argv)
// {
//     (void)argc;
//     (void)argv;
//     t_cub3d *g;
    
//     /*************************************/
//     /********** PARSING PART ************/
//     /***********************************/
    
//     t_vars  *data = malloc(sizeof(t_vars));
//     t_colors *colors = malloc(sizeof(t_colors));
//     t_directions    *dir = malloc(sizeof(t_directions));

//     parsing_part(data, dir, colors);
//     /*********************************/
//     g = NULL;
//     g = prepare_before_ray_casting(g, colors, data, dir);
//     if (!g)
//     {
//         ft_putstr_fd("Error\nMemory allocation failure\n", 2);
//         return (1);
//     }
//     mlx_manage(g);
//     return (0);
// }
