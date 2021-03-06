/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynenakho <ynenakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 19:55:03 by ynenakho          #+#    #+#             */
/*   Updated: 2019/02/28 17:55:02 by ynenakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int main()
{
    t_lemin lemin;
    
    ft_bzero(&lemin, sizeof(t_lemin));
    read_stdin(&lemin);
    
    

    find(lemin.dict, "room1");
    find(lemin.dict, "room2");
    find(lemin.dict, "room3");
    find(lemin.dict, "room4");
    find(lemin.dict, "room5");
    find(lemin.dict, "room6");
    find(lemin.dict, "room7");
    find(lemin.dict, "room8");

    printf("End = %s ind = %d Start = %s ind = %d\n", lemin.end->room_name, lemin.end->index,lemin.start->room_name,lemin.start->index );

    // TEST GRAPH!!!!
    printf("-------------------------");
    // t_graph *graph = createGraph(6);
    // addEdge(graph, 0, 1);
    // addEdge(graph, 0, 2);
    // addEdge(graph, 1, 2);
    // addEdge(graph, 1, 4);
    // addEdge(graph, 1, 3);
    // addEdge(graph, 2, 4);
    // addEdge(graph, 3, 4);
 
    bfs(lemin.graph, lemin.start->index, lemin.end->index, lemin.num_rooms, &lemin);

    return (0);
}

void rooms_to_dict(t_lemin *lemin)
{
    int i = 0;
    t_room *tmp;

    lemin->dict = dictInit(lemin->num_rooms);
    tmp = lemin->linked_rooms;
    while (i < lemin->num_rooms) 
    {
        dictInsert(lemin->dict, tmp->room_name, tmp);
        // tmp->index = i;
        tmp = tmp->next;
        i++;
    }
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

// int g_ind = 0;

t_room *create_room(char *room_name, int x, int y, int start, int end)
{
    static int ind = 0;
    
    t_room *new_room;
    new_room = malloc(sizeof(t_room));
    new_room->room_name = room_name;
    new_room->x = x;
    new_room->y = y;
    new_room->start = (start > 0) ? 1: 0;
    new_room->end = (end > 0) ? 1: 0;
    new_room->index = ind++;
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
    if (*start_flag == 1)
        lemin->start = lemin->linked_rooms;
    if (*end_flag == 1)
        lemin->end = lemin->linked_rooms;
    
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
    char **rooms;

    rooms = ft_strsplit(ft_strtrim(line), '-');
    if (!rooms[0] || !rooms[1])
        exit_error("Error with link format: ", line);
    printf("link = %s - %s\n", ft_strtrim(rooms[0]), ft_strtrim(rooms[1]));
    // printf("|%s| |%s|\n", rooms[0], ft_strtrim(rooms[0]));
    addEdge(lemin, ft_strtrim(rooms[0]), ft_strtrim(rooms[1]));

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
            if (lemin->graph == NULL) {
                rooms_to_dict(lemin);
                lemin->graph = createGraph(lemin->num_rooms);
            }
            if (end_flag != -1 || start_flag != -1)
                exit_error("Start and End point should be defined", "");
            check_links(lemin, line);
        }
    }
    printf("INPUT FINISHED\n");
    print_rooms(lemin->linked_rooms);
    printf("Number of rooms = %d\n", lemin->num_rooms);


}
            