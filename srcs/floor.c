/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:16:11 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/16 16:32:26 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int get_floor_line(t_parsing *parsing)
{
    int i = 0;
    int j = 0;
    parsing->floor_line = 0;
    while (parsing->file[i])
    {
        j = 0;
        while (parsing->file[i][j] && parsing->file[i][j] != '\n')
        {
            if (parsing->file[i][j] == 'F')
            {
                parsing->floor_line = i;
                return 1;
            }
            j++;
        }
        i++;
    }
    return 0;
}

int set_floor(t_parsing *parsing)
{
    int j = 0;
    if (!get_floor_line(parsing))
        return 0;
    //parsing->first_floor = -1;
    //parsing->last_floor = -1;
    while (parsing->file[parsing->floor_line][j] && parsing->file[parsing->floor_line][j] != '\n')
    {

        if (parsing->file[parsing->floor_line][j] == 'F')
        {
            parsing->first_floor = j;
            while (parsing->file[parsing->floor_line][j] != '\n'&& parsing->file[parsing->floor_line][j])
            {
                parsing->last_floor = j;
                j++;
            }
            break;
        }
        j++;
    }
    if (parsing->first_floor  == -1 || parsing->last_floor == -1)
        return 0;
    return 1;
}
int assign_floor(t_parsing *parsing, int count)
{
    int j = 0;
    int k = 0;
    parsing->floor = malloc(sizeof(char) * (count + 1));
    if (!parsing->floor)
        return 0;
    while (parsing->file[parsing->floor_line][j] && k < count)
    {
        if (parsing->file[parsing->floor_line][j] != ' ' &&
            parsing->file[parsing->floor_line][j] != '\t')
        {
            parsing->floor[k] = parsing->file[parsing->floor_line][j];
            k++;
        }
        j++;
    }
    parsing->floor[k] = '\0';
    return 1;
}

int init_floor(t_parsing *parsing)
{
    int j = 0;
    if (!set_floor(parsing))   
         return 0;
    int save_first = parsing->first_floor;
    int save_last = parsing->last_floor;
    int count = 0; 
    while (parsing->file[parsing->floor_line][j] && parsing->file[parsing->floor_line][j] != '\n')
    {
            if (parsing->file[parsing->floor_line][j] != ' ' && parsing->file[parsing->floor_line][j] != '\t')
                count++;
        j++;       
    }
    parsing->first_floor =save_first ;
    parsing->last_floor = save_last;
    //parsing->floor = NULL;
    if (!assign_floor(parsing,count))
        return 0;
    return 1; 
}