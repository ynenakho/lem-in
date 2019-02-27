/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynenakho <ynenakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 19:55:03 by ynenakho          #+#    #+#             */
/*   Updated: 2019/02/26 23:51:37 by ynenakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int main()
{
    // t_lemin lemin;

    // ft_bzero(&lemin, sizeof(t_lemin));
    // read_stdin(&lemin);
    

    // TEST GRAPH!!!!
    t_graph *graph = createGraph(6);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 4);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
 
    bfs(graph, 0, 4, 4);

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

void check_num_of_ants(char *line, t_lemin *lemin)
{
    int int_to_check;

    int_to_check = ft_atoi(line);
    if(!ft_strcmp(line, ft_itoa(int_to_check)))
        lemin->num_of_ants = int_to_check;
    else
        exit_error("Number of ants is in a wrong format: ", line);
}

t_room *create_room(char *room_name, int x, int y, bool start, bool end)
{
    t_room *new_room;
    new_room = malloc(sizeof(t_room));
    new_room->room_name = room_name;
    new_room->x = x;
    new_room->y = y;
    new_room->start = start;
    new_room->end = end;
    new_room->next = NULL;
    return new_room;
}

t_room *add_to_rooms(t_room *head, t_room *room_to_add)
{
    room_to_add->next = head;
    head = room_to_add;
    return head;
}

void check_room_coords(char *line, t_lemin *lemin, int *start_flag, int *end_flag, int *run_count)
{
    int sosi;
    if (lemin || *run_count)
        sosi = 0;

    char **result;

    char *room_name;
    result = ft_strsplit(line, ' ');
    if (result[0] && !result[1])
    {
        *run_count = 3;
        return;
    }

    if (!result[0] || !result[1] || !result[2])
        exit_error("Error with coordinates format: ", line);
    room_name = result[0];
    int x = atoi(result[1]);
    int y = atoi(result[2]);
    printf("coord = %s %d %d start = %d end = %d\n", room_name, x, y, *start_flag, *end_flag);
    if (!lemin->linked_rooms)
        lemin->linked_rooms = create_room(room_name, x, y, *start_flag, *end_flag);
    else
        lemin->linked_rooms = add_to_rooms(lemin->linked_rooms, create_room(room_name, x, y, *start_flag, *end_flag));
    lemin->num_rooms++;
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
    {
        ft_putendl(line);
        return (1);
    }
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
    printf("link = %s - %s\n", ft_strtrim(rooms[0]), ft_strtrim(rooms[1]));
}

void print_rooms(t_room *rooms)
{
    while (rooms)
    {
        printf("Name = %s x = %d y = %d\n", rooms->room_name, rooms->x, rooms->y);
        rooms = rooms->next;
    }
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
        if (run_count == 2)
            check_room_coords(line, lemin, &start_flag, &end_flag, &run_count);
        if (run_count == 3)
        {
            if (end_flag != -1 || start_flag != -1)
                exit_error("Start and End point should be defined", "");
            check_links(lemin, line);
        }
    }
    printf("INPUT FINISHED\n");
    print_rooms(lemin->linked_rooms);
    printf("Number of rooms = %d\n", lemin->num_rooms);
}
            