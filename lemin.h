/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynenakho <ynenakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 19:58:16 by ynenakho          #+#    #+#             */
/*   Updated: 2019/02/22 15:07:41 by ynenakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# include "libft/libft.h"
# define SIZE 40


typedef struct  s_lemin
{
    int     num_of_ants;
    char    *input;

}               t_lemin;

/*
** BFS stucts
*/

typedef struct  s_queue 
{
    int items[SIZE];
    int front;
    int rear;
}               t_queue;


typedef struct  s_node
{
    int vertex;
    struct s_node *next;
}               t_node;



typedef struct s_graph
{
    int numVertices;
    t_node **adjLists;
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
void enqueue(t_queue *q, int);
int dequeue(t_queue *q);
int vertex;
void display(t_queue *q);
int isEmpty(t_queue *q);
void printQueue(t_queue *q);

t_node *createNode(int);

t_graph *createGraph(int vertices);
void addEdge(t_graph *graph, int src, int dest);
void printGraph(t_graph *graph);
void bfs(t_graph *graph, int startVertex);

#endif