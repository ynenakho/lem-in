/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynenakho <ynenakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 19:55:03 by ynenakho          #+#    #+#             */
/*   Updated: 2019/02/22 22:07:31 by ynenakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int main()
{
    t_lemin lemin;

    ft_bzero(&lemin, sizeof(t_lemin));
    read_stdin(&lemin);
    
    ft_putstr(lemin.input);



    // TEST GRAPH!!!!
    // struct Graph* graph = createGraph(6);
    // addEdge(graph, 0, 1);
    // addEdge(graph, 0, 2);
    // addEdge(graph, 1, 2);
    // addEdge(graph, 1, 4);
    // addEdge(graph, 1, 3);
    // addEdge(graph, 2, 4);
    // addEdge(graph, 3, 4);
 
    // bfs(graph, 0);





    return (0);
}

int	go_gnl(int i, char **line)
{
	if (*line)
	{
		ft_bzero(*line, ft_strlen(*line));
		free(*line);
	}
	return (get_next_line(i, line));
}

// int check_number(char *str_to_check)
// {
//     int int_to_check;
//     int_to_check = ft_atoi(str_to_check);
//     if(!ft_strcmp(str_to_check, ft_itoa(int_to_check)))
//         return (1);
//     return (0);
// }


void check_num_of_ants(char *line, t_lemin *lemin)
{
    int int_to_check;

    int_to_check = ft_atoi(line);
    if(!ft_strcmp(line, ft_itoa(int_to_check)))
        lemin->num_of_ants = int_to_check;
    else
        exit_error("Number of ants is in a wrong format: ", line);
}

void check_room_coords(char *line, t_lemin *lemin, int *start_flag, int *end_flag, int *run_count)
{
    int sosi;
    if (lemin || *run_count)
        sosi = 0;

    char **result;

    char *point_name;
    result = ft_strsplit(line, ' ');
    if (result[0] && !result[1])
    {
        *run_count = 3;
        return;
    }

    if (!result[0] || !result[1] || !result[2])
        exit_error("Error with coordinates format: ", line);
    point_name = result[0];
    int first_coord = atoi(result[1]);
    int second_coord = atoi(result[2]);
    printf("coord = %s %d %d start = %d end = %d\n", point_name, first_coord, second_coord, *start_flag, *end_flag);
    *start_flag = (*start_flag == 1 || *start_flag == -1) ? -1: 0;
    *end_flag = (*end_flag == 1 || *end_flag == -1) ? -1: 0;
}

int check_for_errors(char *line, int *start_flag, int *end_flag)
{
    if (line[0] == 'L')
        exit_error("Command cant start with 'L': ", line);
    if (!ft_strcmp(ft_strtrim(line), "##start"))
    {
        if (*start_flag == -1)
            exit_error("Two start points detected", NULL);
        ft_putstr("start detected\n");
        *start_flag = 1;
        return (1);
    }
    if (!ft_strcmp(ft_strtrim(line), "##end"))
    {
        if (*end_flag == -1)
            exit_error("Two end points detected", NULL);
        ft_putstr("end detected\n");
        *end_flag = 1;
        return (1);
    }
    if (line[0] == '#')
        return (1);
    return (0);
}

void check_links(t_lemin *lemin, char *line)
{
    int sosi;
    if (lemin)
        sosi = 0;

    char **rooms;

    rooms = ft_strsplit(ft_strtrim(line), '-');
    if (!rooms[0] || !rooms[1])
        exit_error("Error with link format: ", line);
    printf("link = %s - %s\n", rooms[0], rooms[1]);
}

void read_stdin(t_lemin *lemin) {
    char *line;
    int run_count = 1;
    int start_flag = 0;
    int end_flag = 0;
    while (get_next_line(0, &line)) {
        if (check_for_errors(line, &start_flag, &end_flag))
            continue ;
        if (run_count == 1)
        {
            check_num_of_ants(line, lemin);
            run_count = 2;
            continue ;
        }
        // printf("HERE!!!!");
        if (run_count == 2)
            check_room_coords(line, lemin, &start_flag, &end_flag, &run_count);
        if (run_count == 3)
        {
            if (end_flag != -1 || start_flag != -1)
                exit_error("Start and End point should be defined", "");
            check_links(lemin, line);
        }
    }
}
            