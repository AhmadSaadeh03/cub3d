/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 18:56:44 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/11 20:01:52 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
void free_file(char **file)
{
    int i = 0;
    if (!file)
        return;
    while (file[i])
        free(file[i++]);
    free(file);
}
void free_directions(t_directions *directions)
{
    if (directions->east)
        free(directions->east);
    if (directions->north)
        free(directions->north);
    if (directions->south)
        free(directions->south);
    if (directions->west)
        free(directions->west);
    if (directions)
        free(directions);
}
void free_parsing(t_parsing *parsing)
{
    if (parsing->file)
        free_file(parsing->file);
    if (parsing)
        free(parsing);
}

void exit_and_error(t_parsing *parsing ,t_directions *directions,char *str)
{
    free_parsing(parsing);
    free_directions(directions);
    printf("Error\n%s",str);
    exit (1);
}
void set_directions(t_parsing *parsing,t_directions *directions)
{
    // if (!set_north(parsing,directions))
    //     return 0;
    //  if (!set_south(parsing,directions))
    //     return 0;
    // if (!set_east(parsing,directions))
    //     return 0;
    //  if (!set_west(parsing,directions))
    //     return 0;
    // return 1;
        init_directions(directions);

        if (!set_texture_path(parsing, &directions->north, "NO"))
            exit_and_error(parsing,directions,"uncorrect NO");
        if (!set_texture_path(parsing, &directions->south, "SO"))
             exit_and_error(parsing,directions,"uncorrect SO");
        if (!set_texture_path(parsing, &directions->east, "EA"))
            exit_and_error(parsing,directions,"uncorrect EA");
        if (!set_texture_path(parsing, &directions->west, "WE"))
            exit_and_error(parsing,directions,"uncorrect WE");
    }
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
    set_directions(parsing,directions);
    //set_ceil(parsing);
    printf("east :%s\n",directions->east);
    printf("west :%s\n",directions->west);
    printf("north :%s\n",directions->north);
    printf("south :%s",directions->south);
    free_parsing(parsing);
    free_directions(directions);
}