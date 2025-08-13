/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 21:04:54 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/13 21:06:20 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int check_elements(t_vars *vars)
{
    int i = 0;
    int j = 0;
    int count = 0;
    while (vars->map[i])
    {
        j = 0;
        while (vars->map[i][j])
        {
            if (vars->map[i][j] == '1' ||vars->map[i][j] == '0' || vars->map[i][j] == ' ')
            {
                j++;
                continue;
            }
            if (vars->map[i][j] == 'N' || vars->map[i][j] == 'E' || vars->map[i][j] == 'S' || vars->map[i][j] == 'W')
            {
                vars->facing_dir = vars->map[i][j];
                vars->xp_pos = i;
                vars->yp_pos = j;
                count++;
                j++;
                continue;
            }
            else
            {
                printf("Error\nundefined element inside the map");
                return 0;
            }
        }
        i++;
    }
    if (count != 1)
    {
        printf("Error\nthere is one or more than one player");
        return 0;
    }
    return 1;
}
int check_taps(t_vars *vars)
{
    int i = 0;

    while (vars->map[i])
    {
        int j = 0;
        int first = -1;
        int last = -1;

        while (vars->map[i][j] && vars->map[i][j] != '\n')
        {
            if (vars->map[i][j] != ' ' && vars->map[i][j] != '\t')
            {
                first = j;
                break;
            }
            j++;
        }
        if (first == -1)
        {
            printf("Error\nempty line inside map");
            return 0;
        }
        j = 0;
        while (vars->map[i][j] && vars->map[i][j] != '\n')
        {
            if (vars->map[i][j] != ' ' && vars->map[i][j] != '\t')
                last = j;
            j++;
        }
        j = first;
        while (j <= last)
        {
            if (vars->map[i][j] == '\t')
            {
                printf("Error\nTab found at line %d, column %d\n", i, j);
                return 0;
            }
            j++;
        }
        i++;
    }
    if (!check_elements(vars))
        return 0;
    return 1;
}

int check_walls_two(t_vars *vars)
{
    int i = 0;
    int j = 0;

    char first_char;
    char last_char;
    while (vars->map[i])
    {
        j = 0;
        while (vars->map[i][j] != '\n' && vars->map[i][j])
        {
            if (vars->map[i][j] != ' ' && vars->map[i][j] != '\t')
            {
                first_char = vars->map[i][j];
                if(first_char == '1')
                    break;
                else
                {
                    printf("Error\nnot sourrounded by walls first index");
                    return 0;
                }
            }
            j++;
        }     
     i++;
    }
    i = 0;
    j = 0;
    while (vars->map[i])
    {
        j = 0;
        while (vars->map[i][j] != '\n' && vars->map[i][j])
            j++;
        j--;
        while (j >= 0)
        {
            while ((vars->map[i][j] == ' ' || vars->map[i][j] == '\t') && j > 0)
                j--;
            last_char =vars->map[i][j];
            if(last_char == '1')
                break;
            else
            {
                printf("Error\nnot sourrounded by walls last index");
                return 0;
            }
        }
        i++;
    }
    return 1;  
}
int check_walls(t_vars *vars)
{
    int i = 0;
    int j = 0;
    int final_line;
    if (!check_taps(vars))
        return 0;
    while (vars->map[i])
    {
        if(vars->map[i][j] == '1' && vars->map[i][j+1] == '1' && vars->map[i][j+2] == '1'  && vars->map[i][j+3] == '1')
            final_line = i;
        i++;
    }
    while (vars->map[0][j] && vars->map[0][j] != '\n')
    {
        if(vars->map[0][j] == ' ' || vars->map[0][j] == '\t' || vars->map[0][j] == '1')
            j++;
        else
        {
            printf("Error\nthe map not sourrounded by walls on top");
            return 0;
        }
    }
    j = 0;
    while (vars->map[final_line][j] && vars->map[final_line][j] != '\n')
    {
        if((vars->map[final_line][j] == ' ' || vars->map[final_line][j] == '\t') || (vars->map[final_line][j] == '1'))
            j++;
        else
        {
            printf("Error\nthe map not sourrounded by walls on bottom");
            return 0;
        }
    }
    if (!check_walls_two(vars))
        return 0;
    return 1;
}
t_vars *init_map(t_parsing *parsing)
{
    int line = first_line(parsing);
    if (!line)
    {
        printf("Error\n there is no map\n");
        return NULL;
    }
    int save_line = line;

    t_vars *vars = malloc(sizeof(t_vars));
    if (!vars)
    {
        
    }
    while (parsing->file[line])
        line++;
    int height = line - save_line;
    vars->map = malloc(sizeof(char *) * (height + 1));
    if (!vars->map)
    {
        free(vars);
        return NULL;
    }
    int i = 0;
    while (i < height)
    {
        int j = 0;
        while (parsing->file[save_line][j] && parsing->file[save_line][j] != '\n')
            j++;
        vars->map[i] = malloc(sizeof(char) * (j + 1));
        if (!vars->map[i])
        {
            int k = 0;
            while (k < i)
            {
                free(vars->map[k]);
                free(vars->map);
                free(vars);
            }     
            return NULL;
        }
        ft_strlcpy(vars->map[i], parsing->file[save_line], j + 1);
        save_line++;
        i++;
    }
    vars->map[height] = NULL;
    return vars;
}