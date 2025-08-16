/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceil.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 20:07:24 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/16 18:47:13 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
//// chat gpt --> for testing 
// void check_number_in_ceil(t_parsing *parsing, t_vars *vars, t_directions *directions)
// {
//     int i = 0;
//     int number_index = 0;
//     t_colors *colors = malloc(sizeof(t_colors));
//     if (!colors)
//         free_all_and_exit(parsing, vars, directions);

//     // Skip until the first digit (start of first number)
//     while (parsing->ceil[i] && !ft_isdigit(parsing->ceil[i]))
//         i++;

//     while (number_index < 3 && parsing->ceil[i])
//     {
//         // Read number with ft_atoi
//         colors->ceil[number_index] = ft_atoi(&parsing->ceil[i]);
//         number_index++;

//         // Skip the number we just parsed
//         while (ft_isdigit(parsing->ceil[i]))
//             i++;

//         // Skip commas or spaces
//         if (parsing->ceil[i] == ',')
//             i++;
//         while (parsing->ceil[i] == ' ' || parsing->ceil[i] == '\t')
//             i++;
//     }

//     if (number_index != 3)
//     {
//         printf("Error\nCeil color must have exactly 3 numbers (R,G,B)\n");
//         free(colors);
//         free_all_and_exit(parsing, vars, directions);
//     }

//     printf("Ceil RGB: %d, %d, %d\n", colors->ceil[0], colors->ceil[1], colors->ceil[2]);

//     free(colors);
// }

void check_comma_in_ceil(t_parsing *parsing,t_vars *vars,t_directions *directions)
{
    int i = 0;
    int count_comma = 0;
    while (parsing->ceil[i])
    {
        if (parsing->ceil[i] == ',')
        {
            if (!ft_isdigit(parsing->ceil[i+1]) || !ft_isdigit(parsing->ceil[i-1]))
            {
                printf("Error\non the place of comma");
                free_all_and_exit(parsing,vars,directions);
            }
            count_comma++;
        }
        if (!ft_isalnum(parsing->ceil[i]) && parsing->ceil[i] != ',' && parsing->ceil[i] != 'C')
        {
            printf("Error\ninvalid char on ceil line");
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
        free_all_and_exit(parsing,vars,directions);
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
   // check_number_in_ceil(parsing,vars,directions);
}