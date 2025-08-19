/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 18:56:44 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/19 18:05:41 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void check_lines(t_parsing *parsing,t_vars *vars,t_directions *directions)
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
            if(parsing->file[i][j] == '1' && is_this_map(parsing,i))
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
    {
        printf("Error\nthe numbers of resources is wrong");
        free_all_and_exit(parsing,vars,directions);
    }
    init_ceil(parsing,vars,directions);

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
        while (parsing->file[i][j] && parsing->file[i][j]!= '\n')
        {
            if (parsing->file[i][j] == '1' && is_this_map(parsing,i))
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
    if (!init_parsing_directions(parsing,directions,argv[1]))
        return 1;
    t_vars *vars = init_map(parsing);
    if (!vars)
        free_all_and_exit(parsing,vars,directions);
    check_image_path(parsing,vars,directions);
    check_lines(parsing,vars,directions);
    check_walls(parsing,vars,directions);
    init_colors(parsing,vars,directions);
}
