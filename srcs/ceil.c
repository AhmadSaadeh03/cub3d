/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceil.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:07:24 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/14 20:09:26 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int get_ceil_line(t_parsing *parsing)
{
    int i = 0;
    int j = 0;
    parsing->ceil_line = 0;
    while (parsing->file[i])
    {
        j = 0;
        while (parsing->file[i][j] && parsing->file[i][j] != '\n')
        {
            if (parsing->file[i][j] == 'C')
            {
                parsing->ceil_line = i;
                return 1;
            }
            j++;
        }
        i++;
    }
    return 0;
}

int set_ceil(t_parsing *parsing)
{
    int j = 0;
    if (!get_ceil_line(parsing))
        return 0;
    parsing->first_ceil = -1;
    parsing->last_ceil = -1;
    while (parsing->file[parsing->ceil_line][j] && parsing->file[parsing->ceil_line][j] != '\n')
    {

        if (parsing->file[parsing->ceil_line][j] == 'C')
        {
            parsing->first_ceil = j;
            while (parsing->file[parsing->ceil_line][j] != '\n'&& parsing->file[parsing->ceil_line][j])
            {
                parsing->last_ceil = j;
                j++;
            }
            break;
        }
        j++;
    }
    if (parsing->first_ceil  == -1 || parsing->last_ceil == -1)
    {
        printf("hsdds");
        return 0;
    }
    return 1;
}
int assign_ceil(t_parsing *parsing, int count)
{
    int j = 0;
    int k = 0;

    parsing->ceil = malloc(sizeof(char) * (count + 1));
    if (!parsing->ceil)
        return 0;
    while (parsing->file[parsing->ceil_line][j] && k < count)
    {
        if (parsing->file[parsing->ceil_line][j] != ' ' &&
            parsing->file[parsing->ceil_line][j] != '\t')
        {
            parsing->ceil[k] = parsing->file[parsing->ceil_line][j];
            k++;
        }
        j++;
    }
    parsing->ceil[k] = '\0';
    return 1;
}

int init_ceil(t_parsing *parsing)
{
    int j = 0;
    if (!set_ceil(parsing))   
         return 0;
    int save_first = parsing->first_ceil;
    int save_last = parsing->last_ceil;
    int count = 0; 
    while (parsing->file[parsing->ceil_line][j] && parsing->file[parsing->ceil_line][j] != '\n')
    {
            if (parsing->file[parsing->ceil_line][j] != ' ' && parsing->file[parsing->ceil_line][j] != '\t')
                count++;
        j++;       
    }
    parsing->first_ceil =save_first ;
    parsing->last_ceil = save_last;
    parsing->ceil = NULL;
    if (!assign_ceil(parsing,count))
        return 0;
    return 1; 
}