/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:16:11 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/16 17:45:36 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void check_comma_in_floor(t_parsing *parsing,t_vars *vars,t_directions *directions)
{
    int i = 0;
    int count_comma = 0;
    while (parsing->floor[i])
    {
        if (parsing->floor[i] == ',')
        {
            if (!ft_isdigit(parsing->floor[i+1]) || !ft_isdigit(parsing->floor[i-1]))
            {
                printf("Error\non the place of comma");
                free_all_and_exit(parsing,vars,directions);
            }
            count_comma++;
        }
        if (!ft_isalnum(parsing->floor[i]) && parsing->floor[i] != ',' && parsing->floor[i] != 'F')
        {
            printf("Error\ninvalid char on floor line");
            free_all_and_exit(parsing,vars,directions);
        }
        i++;
    }
    if (count_comma != 2)
    {
        printf("Error\nthe number of comma is wrong");
        free_all_and_exit(parsing,vars,directions);
    }
}
void check_letter_on_floor(t_parsing *parsing,t_vars *vars,t_directions *directions)
{
    int i = 0;
    int count = 0;
    char c;
    while (parsing->file[parsing->floor_line][i] != '\n' && parsing->file[parsing->floor_line][i])
    {
        if (ft_isalpha(parsing->file[parsing->floor_line][i]))
        {
            c = parsing->file[parsing->floor_line][i];
            count++;
        }
       i++;
    }
    if (count != 1 || c != 'F')
    {
        printf("Error\nto many letters on floor line");
        free_all_and_exit(parsing,vars,directions);
    } 
}
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

void set_floor(t_parsing *parsing,t_vars *vars,t_directions *directions)
{
    int j = 0;
    if (!get_floor_line(parsing))
        free_all_and_exit(parsing,vars,directions);
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
       free_all_and_exit(parsing,vars,directions);
}
void assign_floor(t_parsing *parsing,t_vars *vars,t_directions *directions, int count)
{
    int j = 0;
    int k = 0;
    parsing->floor = malloc(sizeof(char) * (count + 1));
    if (!parsing->floor)
        free_all_and_exit(parsing,vars,directions);
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
}

void init_floor(t_parsing *parsing,t_vars *vars,t_directions *directions)
{
    int j = 0;
    set_floor(parsing,vars,directions);
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
    assign_floor(parsing,vars,directions,count);
    check_letter_on_floor(parsing,vars,directions);
    check_comma_in_floor(parsing,vars,directions);
}