/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynenakho <ynenakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 19:58:16 by ynenakho          #+#    #+#             */
/*   Updated: 2019/02/27 15:29:37 by ynenakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# include "libft/libft.h"
# include <stdbool.h>

typedef struct  s_room
{
    char *room_name;
    int x;
    int y;
    int index;
    int start;
    int end;
    struct s_room *next;
}               t_room;

typedef struct s_item {
	char           *key; //here the key will be the name
	t_room *room; // struct s_art   *value;
	struct s_item  *next;
}               t_item;

typedef struct s_dict {
	t_item      **items;
	int           capacity; //the capacity of the array 'items'
}               t_dict;

typedef struct  s_lemin
{
    t_room  *start;
    t_room  *end;
    int     num_rooms;
    int     num_of_ants;
    t_room  *linked_rooms;
    t_dict  *dict;
}               t_lemin;

/*
** BFS stucts
*/

typedef struct  s_queue 
{
    int *items;
    int front;
    int rear;
}               t_queue;

typedef struct  s_node
{
    // char *room_name;
    int vertex;
    struct s_node *next;
}               t_node;

typedef struct s_graph
{
    int num_rooms; // int numVertices;
    t_node **adjLists;
    // char **room_names;
    int *visited;
}              t_graph;

/*
** Main functionallity
*/

void read_stdin(t_lemin *lemin);
void exit_error(char *msg, char* arg);

/*
** BFS (queue)
*/

t_queue *createQueue();
void enqueue(t_queue *q, int value, int size);
int dequeue(t_queue *q);
void display(t_queue *q);
int isEmpty(t_queue *q);
void printQueue(t_queue *q);

t_node *createNode(int);

t_graph *createGraph(int vertices);
void addEdge(t_graph *graph, int src, int dest);
void printGraph(t_graph *graph);
void bfs(t_graph *graph, int startVertex, int endVertex, int size);


// DICTIONNARY

size_t hash(char *input); //return hash result

t_dict *dictInit(int capacity); //initialize the dictionnary, given as parameter the capacity of the array.
int	dictInsert(t_dict *dict, char *key, t_room *room); //add one element in the dictionnary, if FAIL return 0, otherwise 1
t_room *dictSearch(t_dict *dict, char *key); //find one element in the dictionnary, if not found, return NULL
void		find(t_dict *d, char *key);
void rooms_to_dict(t_lemin *lemin);

#endif