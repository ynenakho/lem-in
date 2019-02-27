/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynenakho <ynenakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:08:06 by ynenakho          #+#    #+#             */
/*   Updated: 2019/02/27 00:00:02 by ynenakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void bfs(t_graph *graph, int startVertex, int endVertex, int size)
{
    int currentVertex;
    int adjVertex;
    t_node *temp;
    t_queue *q;
    int count = 0;

    q = createQueue(size);
    graph->visited[startVertex] = 1;
    enqueue(q, startVertex, size);
    while(!isEmpty(q))
    {
        count = 0;
        printQueue(q);
        currentVertex = dequeue(q);
        printf("Visited %d\n", currentVertex);
        
        temp = graph->adjLists[currentVertex];
        while(temp)
        {
            adjVertex = temp->vertex;
            if(graph->visited[adjVertex] == 0)
            {
                count++;
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex, size);
                
            }
            
            
            temp = temp->next;
            
       }
       if (currentVertex == endVertex) 
                    printf("Count = %d\n", count);
    }
}

t_node *createNode(int v)
{
    t_node *newNode;
    newNode = malloc(sizeof(t_node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}
 

t_graph *createGraph(int rooms)
{
    t_graph *graph;
    int i;

    graph = malloc(sizeof(t_graph));
    graph->num_rooms = rooms;
    graph->adjLists = malloc(rooms * sizeof(t_node*));
    graph->visited = malloc(rooms * sizeof(int));
    i = 0;
    while (i < rooms)
    {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
        i++;
    }
    return graph;
}
 
void addEdge(t_graph *graph, int ind_from, int ind_to)
{
    // Add edge from src to dest
    t_node *newNode;

    newNode = createNode(ind_to);
    newNode->next = graph->adjLists[ind_from];
    graph->adjLists[ind_from] = newNode;
 
    // Add edge ind_from ind_to ind_to ind_from
    newNode = createNode(ind_from);
    newNode->next = graph->adjLists[ind_to];
    graph->adjLists[ind_to] = newNode;
}

t_queue* createQueue(int size) {
    t_queue* q;

    q = malloc(sizeof(t_queue));
    q->items = malloc(sizeof(int) * size);
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(t_queue* q)
{
    if(q->rear == -1) 
        return 1;
    else 
        return 0;
}

void enqueue(t_queue* q, int value, int size)
{
    if(q->rear == size - 1)
        printf("\nQueue is Full!!");
    else
    {
        if(q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

int dequeue(t_queue* q)
{
    int item;
    if (isEmpty(q))
    {
        printf("Queue is empty");
        item = -1;
    }
    else
    {
        item = q->items[q->front];
        q->front++;
        if(q->front > q->rear)
        {
            printf("Resetting queue");
            q->front = q->rear = -1;
        }
    }
    return item;
}

void printQueue(t_queue *q)
{
    int i;

    i = q->front;
    if(isEmpty(q))
        printf("Queue is empty");
    else
    {
        printf("\nQueue contains \n");
        while(i < q->rear + 1)
        {
            printf("%d ", q->items[i]);
            i++;
        }
    }    
}