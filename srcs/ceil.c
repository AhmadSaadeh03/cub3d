/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceil.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:07:24 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/17 14:53:48 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
char *init_ceil_numbers(t_parsing *parsing,t_vars *vars,t_directions *directions)
{
    int i = 1; 
    int j = 0;
    char *line;
    int count = ft_strlen(parsing->ceil);
    count-=1;
    line  = malloc(sizeof(char) * count + 1);
    if (!line)
        free_all_and_exit(parsing,vars,directions);
    while (parsing->ceil[i])
    {
        line[j] = parsing->ceil[i];
        i++;
        j++;
    }
    line[j] = '\0';
    return line;
}
t_colors *get_ceil_number(t_parsing *parsing,t_vars *vars,t_directions *directions)
{
    int i = 0;
    char **string;
    char *line = init_ceil_numbers(parsing,vars,directions);
    t_colors *colors = malloc(sizeof(t_colors));
    if (!colors)
    {
        free(line);
        free_all_and_exit(parsing,vars,directions);
    }
    string = ft_split(line,',');
    if (!string)
    {
        free(line);
        free(colors);
        free_all_and_exit(parsing,vars,directions);
    }
    colors->ceil[0] = ft_atoi(string[0]);
    colors->ceil[1] = ft_atoi(string[1]);
    colors->ceil[2] = ft_atoi(string[2]);
    while (string[i])
    {
        free(string[i]);
        i++;
    }
    free(string);
    free(line);
    get_floor_number(parsing,vars,directions,colors);
    check_valid_numbers(parsing,vars,directions,colors);
    return colors;
}

void check_comma_in_ceil(t_parsing *parsing,t_vars *vars,t_directions *directions)
{
    int i = 0;
    int count_comma = 0;
    while (parsing->ceil[i])
    {
        if (!ft_isalnum(parsing->ceil[i]) && parsing->ceil[i] != ',' && parsing->ceil[i] != 'C')
        {
            printf("Error\ninvalid char in ceil line");
            free_all_and_exit(parsing,vars,directions);
        }
        if (parsing->ceil[i] == ',')
        {
            if (!ft_isdigit(parsing->ceil[i+1]) || !ft_isdigit(parsing->ceil[i-1]))
            {
                printf("Error\nafter and before comma should be number in ceil line");
                free_all_and_exit(parsing,vars,directions);
            }
            count_comma++;
        }
        i++;
    }
    if (count_comma != 2)
    {
        printf("Error\nthe number of comma is wrong in ceil line");
        free_all_and_exit(parsing,vars,directions);
    }
}
void    check_letter_on_ceil(t_parsing *parsing,t_vars *vars,t_directions *directions)
{
    int i = 0;
    int count = 0;
    char c;
    while (parsing->file[parsing->ceil_line][i] != '\n' && parsing->file[parsing->ceil_line][i])
    {
        if (ft_isalpha(parsing->file[parsing->ceil_line][i]))
        {
            c = parsing->file[parsing->ceil_line][i];
            count++;
        }
       i++;
    }
    if (count != 1 || c != 'C')
    {
        printf("Error\non ceil line");
        free_all_and_exit(parsing,vars,directions);
    }
}

int get_ceil_line(t_parsing *parsing)
{
    int i = 0;
    int j = 0;
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

void set_ceil(t_parsing *parsing,t_vars *vars,t_directions *directions)
{
    int j = 0;
    if (!get_ceil_line(parsing))
    {
        write(2, "Error\nC Rule Does Not Found\n", 29);
        free_all_and_exit(parsing,vars,directions);
    }
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
        free_all_and_exit(parsing,vars,directions);
}
void assign_ceil(t_parsing *parsing,t_vars *vars,t_directions *directions, int count)
{
    int j = 0;
    int k = 0;

    parsing->ceil = malloc(sizeof(char) * (count + 1));
    if (!parsing->ceil)
       free_all_and_exit(parsing,vars,directions);
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
}

void init_ceil(t_parsing *parsing,t_vars *vars,t_directions *directions)
{
    int j = 0;
    set_ceil(parsing,vars,directions);
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
    assign_ceil(parsing,vars,directions,count);
    init_floor(parsing,vars,directions);
    check_letter_on_ceil(parsing,vars,directions);
    check_comma_in_ceil(parsing,vars,directions);
    // t_colors *colors  = check_number_in_ceil(parsing,vars,directions);
    // if (!colors)
    // {
    //     free(colors);
    //     free_all_and_exit(parsing,vars,directions);
    // }
    // printf("%d\n%d\n%d\n",colors->ceil[0],colors->ceil[1],colors->ceil[2]);
}