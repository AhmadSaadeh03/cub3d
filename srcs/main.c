/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 18:56:44 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/12 20:44:41 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// void init_colors(t_colors *colors)
// {
//     colors->ceil[0] = 0;
//     colors->ceil[1] = 0;
//     colors->ceil[2] = 0;
//     colors->floor[0] = 0;
//     colors->floor[1] = 0;
//     colors->floor[2] = 0;
// }
// int set_ceil(t_parsing *parsing)
// {
//     t_colors *colors = malloc(sizeof(t_colors));
//     if (!colors)
//         return 0;
//     init_colors(colors);
//     int i = 0;
//     int j = 0;
//     while (parsing->file[i])
//     {
//         j = 0;
//         while (parsing->file[i][j])
//         {
//             if (parsing->file[i][j] == 'C' && !ft_isalpha(parsing->file[i][j+1]))
//             {
//                 while (parsing->file[i][j] == ' ' || parsing->file[i][j] == '\t')
//                     j++;
                

//             }
//             j++;
//         }
        
//         i++;
//     }
    

// }
int count_lines(char *file_name)
{
    int fd;
    int i = 0;
    char    *line;

    fd = open(file_name,O_RDONLY);
    if (fd == -1)
        return 0;
    while ((line = get_next_line(fd)))
    {
        i++;
        free(line);
    }
    close(fd);
    return i;
}

char  **read_file(char *file_name)
{
    char *line;
    int i = 0;
    int len = count_lines(file_name);

    if (len <= 0)
        return NULL;
    int fd;
    fd = open(file_name,O_RDONLY);
    if (fd == -1)
        return NULL;
    char **file = malloc(sizeof(char *) * (len + 1));
    if (!file)
        return NULL;
    while ((line = get_next_line(fd)))
    {
        file[i] = line;
        i++;
    }
    file[i] = NULL;
    close(fd);
    return file;
}
int valid_extension(char **argv)
{
    char *name = argv[1];
    int len = ft_strlen(name);
    if (name[len -1] == 'b' && name[len - 2]  == 'u' && name[len - 3]  == 'c' 
        && name[len - 4]  == '.' && ft_isalnum(name[len - 5]))
        return 1;
    return 0;
}

int check_lines(t_parsing *parsing)
{
    int i = 0;
    int j = 0;
    int not_empty = 0;
    int stop = 0;
    while (parsing->file[i])
    {
        j = 0;
        while (parsing->file[i][j] && parsing->file[i][j] != '\n')
        {
            if(parsing->file[i][j] == '1' && parsing->file[i][j+1] == '1' && parsing->file[i][j+2] == '1' && parsing->file[i][j+3] == '1')
            {
                stop = 1;
                break;
            }
            if (ft_isalnum(parsing->file[i][j]))
            {
                not_empty++;
                break;
            }
            j++;
        }
        if (stop)
            break;
        i++;
    }
    if (not_empty != 6)
        return 0;
    return 1;
}
int first_line(t_parsing *parsing)
{
    int i = 0;
    int j = 0;
    int save_line = 0;
    int found = 0;
    while (parsing->file[i])
    {
        j = 0;
        while (parsing->file[i][j] && parsing->file[i][j+3])
        {
            if (parsing->file[i][j] == '1' && parsing->file[i][j+1] == '1' && parsing->file[i][j+2] == '1' && parsing->file[i][j+3] == '1')
            {
                save_line  = i ;
                found = 1;
                break;
            }
            j++;
        }
        if (found)
            break;
        i++;
    }
    if (!found)
        return 0;
    return save_line;
    // j = 0;
    // while (parsing->file[save_line])
    // {
    //     j = 0;
    //     while (parsing->file[save_line][j])
    //     {
    //         printf("%c",parsing->file[save_line][j]);
    //         j++;
    //     }
    //     save_line++;
    // }
    
    return 1;
}
// int init_map(t_parsing *parsing)
// {
//     int line = first_line(parsing);
//     if (!line)
//     {
//         printf("Error\n on the map");
//         exit(1);
//     }
//     int j = 0;
//     int save_line = line;
//     t_vars *vars = malloc(sizeof(t_vars));
//     if (!vars)
//         return 0;
//     while (parsing->file[line])
//         line++;
//     int height = line - save_line;

//     vars->map = malloc(sizeof(char *) * (height + 1));
//     if (!vars->map)
//         return 0;
    
//     int i = 0;
//     j = 0;
//     while (i < height)
//     {
//         j = 0;
//         while (parsing->file[save_line][j] && parsing->file[save_line][j] != '\n')
//             j++;
//         vars->map[save_line] = malloc(sizeof(char) * (j + 1));
//         ft_strlcpy(vars->map[save_line],parsing->file[save_line],ft_strlen(parsing->file[save_line]));
//         save_line++;
//         i++;
//     }
//     return 1;
// }
int init_map(t_parsing *parsing)
{
    int line = first_line(parsing);
    if (!line)
    {
        printf("Error\n on the map\n");
        exit(1);
    }
    int save_line = line;

    t_vars *vars = malloc(sizeof(t_vars));
    if (!vars)
        return 0;
    while (parsing->file[line])
        line++;
    int height = line - save_line;
    vars->map = malloc(sizeof(char *) * (height + 1));
    if (!vars->map)
    {
        free(vars);
        return 0;
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
            return 0;
        }
        ft_strlcpy(vars->map[i], parsing->file[save_line], j + 1);
        save_line++;
        i++;
    }
    vars->map[height] = NULL;
    return 1;
}

int main(int argc ,char **argv)
{
    if (argc != 2)
        return 1;
    if(!valid_extension(argv))
    {
        printf("Error\n the extension of the file is wrong");
        return 1;
    }
    t_parsing *parsing = malloc(sizeof(t_parsing));
    if(!parsing)
        return 1;
    t_directions *directions = malloc(sizeof(t_directions));
    if (!directions)
    {
        free(parsing);
        return 1;
    }
    parsing->file = read_file(argv[1]);
    if (!parsing->file)
    {
            printf("Error\non opening the fd");
            free(parsing);
            free(directions);
            return 1;
    }
    if (!check_lines(parsing))
    {
        printf("Error\nthere is line or more missing");
        free_parsing(parsing);
        free(directions);
        return 1;
    }
    set_directions(parsing,directions);
    init_map(parsing);
    printf("east :%s\n",directions->east);
    printf("west :%s\n",directions->west);
    printf("north :%s\n",directions->north);
    printf("south :%s\n",directions->south);
    free_parsing(parsing);
    free_directions(directions);
}