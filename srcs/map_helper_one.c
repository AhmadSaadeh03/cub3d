/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_helper_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 18:46:56 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/23 16:39:47 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_this_map(t_parsing *parsing, int i)
{
	int	j;

	j = 0;
	while (parsing->file[i][j] && parsing->file[i][j] != '\n')
	{
		if (ft_isalpha(parsing->file[i][j]))
			return (0);
		j++;
	}
	return (1);
}
