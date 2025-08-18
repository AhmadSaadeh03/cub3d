/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaadeh <asaadeh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:37:54 by asaadeh           #+#    #+#             */
/*   Updated: 2025/08/17 17:01:59 by asaadeh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
// int set_north(t_parsing *parsing,t_directions *directions)
// {
//     int i = 0;
//     int j = 0;
//     int save_dot;
//     int endofpath;
//     int correct_line;
//     int k = 0;
//     int flag = 0;
//     init_directions(directions);
//     while (parsing->file[i])
//     {
//         j = 0;
//         while(parsing->file[i][j])
//         {

//             if (parsing->file[i][j] == 'N' && parsing->file[i][j+1] == 'O')
//             {
//                 correct_line = i;
//                 j+=2;
//                 while (parsing->file[i][j] == ' ' || parsing->file[i][j] == '\t')
//                     j++;
//                 if (parsing->file[i][j] != '.' || parsing->file[i][j+1] != '/')
//                 {
//                     return 0;
//                 }
//                 save_dot = j;
//                 while (parsing->file[i][j] && parsing->file[i][j] != '\n')
//                     j++;
//                 endofpath = j;
//                 flag = 1;      
//             }
//             j++;
//         }
//         i++;
//     }
//     if (flag == 1)
//     {
//         directions->north = malloc(sizeof(char) * (endofpath - save_dot)  + 1);
//         if (!directions->north)
//         {
//             free(directions);
//             return 0;
//         }
//         while (save_dot != endofpath)
//         {
//             directions->north[k] = parsing->file[correct_line][save_dot];
//             save_dot++;
//             k++;
//         }
//         directions->north[k] = '\0';
//        // printf(" north :%s\n",directions->north);
//         return 1;
//     }
//     return 0;
    
// }
// int set_south(t_parsing *parsing,t_directions *directions)
// {
//     int i = 0;
//     int j = 0;
//     int save_dot;
//     int endofpath;
//     int correct_line;
//     int k = 0;
//     int flag = 0;
//     while (parsing->file[i])
//     {
//         j = 0;
//         while(parsing->file[i][j])
//         {

//             if (parsing->file[i][j] == 'S' && parsing->file[i][j+1] == 'O')
//             {
//                 correct_line = i;
//                 j+=2;
//                 while (parsing->file[i][j] == ' ' || parsing->file[i][j] == '\t')
//                     j++;
//                 if (parsing->file[i][j] != '.' || parsing->file[i][j+1] != '/')
//                 {
//                     return 0;
//                 }
//                 save_dot = j;
//                 while (parsing->file[i][j] && parsing->file[i][j] != '\n')
//                     j++;
//                 endofpath = j;
//                 flag = 1;      
//             }
//             j++;
//         }
//         i++;
//     }
//     if (flag == 1)
//     {
//         directions->south = malloc(sizeof(char) * (endofpath - save_dot)  + 1);
//         if (!directions->south)
//         {
//             free(directions);
//             return 0;
//         }
//         while (save_dot != endofpath)
//         {
//             directions->south[k] = parsing->file[correct_line][save_dot];
//             save_dot++;
//             k++;
//         }
//         directions->south[k] = '\0';
//         //printf(" south :%s\n",directions->south);
//         return 1;
//     }
//     return 0;
    
// }
// int set_east(t_parsing *parsing,t_directions *directions)
// {
//     int i = 0;
//     int j = 0;
//     int save_dot;
//     int endofpath;
//     int correct_line;
//     int k = 0;
//     int flag = 0;
//     while (parsing->file[i])
//     {
//         j = 0;
//         while(parsing->file[i][j])
//         {

//             if (parsing->file[i][j] == 'E' && parsing->file[i][j+1] == 'A')
//             {
//                 correct_line = i;
//                 j+=2;
//                 while (parsing->file[i][j] == ' ' || parsing->file[i][j] == '\t')
//                     j++;
//                 if (parsing->file[i][j] != '.' || parsing->file[i][j+1] != '/')
//                 {
//                     return 0;
//                 }
//                 save_dot = j;
//                 while (parsing->file[i][j] && parsing->file[i][j] != '\n')
//                     j++;
//                 endofpath = j;
//                 flag = 1;      
//             }
//             j++;
//         }
//         i++;
//     }
//     if (flag == 1)
//     {
//         directions->east = malloc(sizeof(char) * (endofpath - save_dot)  + 1);
//         if (!directions->east)
//         {
//             free(directions);
//             return 0;
//         }
//         while (save_dot != endofpath)
//         {
//             directions->east[k] = parsing->file[correct_line][save_dot];
//             save_dot++;
//             k++;
//         }
//         directions->east[k] = '\0';
//         //printf(" east :%s\n",directions->east);
//         return 1;
//     }
//     return 0;
    
// }
// int set_west(t_parsing *parsing,t_directions *directions)
// {
//     int i = 0;
//     int j = 0;
//     int save_dot;
//     int endofpath;
//     int correct_line;
//     int k = 0;
//     int flag = 0;
//     while (parsing->file[i])
//     {
//         j = 0;
//         while(parsing->file[i][j])
//         {

//             if (parsing->file[i][j] == 'W' && parsing->file[i][j+1] == 'E')
//             {
//                 correct_line = i;
//                 j+=2;
//                 while (parsing->file[i][j] == ' ' || parsing->file[i][j] == '\t')
//                     j++;
//                 if (parsing->file[i][j] != '.' || parsing->file[i][j+1] != '/')
//                 {
//                     return 0;
//                 }
//                 save_dot = j;
//                 while (parsing->file[i][j] && parsing->file[i][j] != '\n')
//                     j++;
//                 endofpath = j;
//                 flag = 1;      
//             }
//             j++;
//         }
//         i++;
//     }
//     if (flag == 1)
//     {
//         directions->west = malloc(sizeof(char) * (endofpath - save_dot)  + 1);
//         if (!directions->west)
//         {
//             free(directions);
//             return 0;
//         }
//         while (save_dot != endofpath)
//         {
//             directions->west[k] = parsing->file[correct_line][save_dot];
//             save_dot++;
//             k++;
//         }
//         directions->west[k] = '\0';
//       //  printf(" west :%s\n",directions->west);
//         return 1;
//     }
//     return 0;
    
// }
int set_dir_path(t_parsing *parsing, char **destination,char *str)
{
    int i = 0;
    int  j = 0;
    int start = 0;
    int end = 0 ;
    int k = 0;
    int found = 0;
    int check = 0;
    while (parsing->file[i])
    {
        j = 0;
        while (parsing->file[i][j])
        {
            if(parsing->file[i][j] == '1' && is_this_map(parsing,i))
            {
                printf("dsfsdf");
                return 0;
            }
            if (parsing->file[i][j] == str[0] && parsing->file[i][j + 1] == str[1])
            {
                j += 2;
                while (parsing->file[i][j] == ' ' || parsing->file[i][j] == '\t')
                    j++;

                if (parsing->file[i][j] != '.' || parsing->file[i][j+1] != '/')
                    return 0;
                start = j;
                while ((parsing->file[i][j] && parsing->file[i][j] != '\n') && (parsing->file[i][j] != ' '&& parsing->file[i][j] != '\t'))
                    j++;
                end = j;
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
     check = j;
     //here i checked if there is any letter after path // 
        while (parsing->file[i][check] != '\n')
        {
            if(ft_isalpha(parsing->file[i][check]))
            {
                printf("errorororroor%d",check);
                return 0;
            }
            check++;
        }
    *destination = malloc(end - start + 1);
    if (!*destination)
        return 0;
    k = 0;
    while (start < end)
        (*destination)[k++] = parsing->file[i][start++];
    (*destination)[k] = '\0';
    return 1;
}
int is_one_time(t_parsing *parsing)
{
    int i = 0;
    int j = 0;
    int count = 0;
    while (parsing->file[i])
    {
        j = 0;
        while (parsing->file[i][j])
        {
            if ((parsing->file[i][j] == 'N' && parsing->file[i][j+1] == 'O') 
            || (parsing->file[i][j] == 'S' && parsing->file[i][j+1] == 'O'))
                count++;
             if ((parsing->file[i][j] == 'E' && parsing->file[i][j+1] == 'A')
              || (parsing->file[i][j] == 'W' && parsing->file[i][j+1] == 'E'))
                count++;
             if ((parsing->file[i][j] == 'F' || parsing->file[i][j] == 'C'))
                count++;
            j++;
        }
        
        i++;
    }
    if (count != 6)
        return 0;
    return 1;
    
}
void set_directions(t_parsing *parsing,t_directions *directions)
{
        init_directions(directions);
        if (!is_one_time(parsing))
            exit_and_error(parsing,directions,"there is more or less than 6 resources");
        if (!set_dir_path(parsing, &directions->north, "NO"))
            exit_and_error(parsing,directions,"uncorrect NO");
        if (!set_dir_path(parsing, &directions->south, "SO"))
             exit_and_error(parsing,directions,"uncorrect SO");
        if (!set_dir_path(parsing, &directions->east, "EA"))
            exit_and_error(parsing,directions,"uncorrect EA");
        if (!set_dir_path(parsing, &directions->west, "WE"))
            exit_and_error(parsing,directions,"uncorrect WE");
    }