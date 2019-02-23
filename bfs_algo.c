/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_algo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynenakho <ynenakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 13:08:06 by ynenakho          #+#    #+#             */
/*   Updated: 2019/02/22 15:06:34 by ynenakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void bfs(t_graph *graph, int startVertex)
{
    int currentVertex;
    int adjVertex;
    t_node *temp;
    t_queue *q;

    q = createQueue();
    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);
    while(!isEmpty(q))
    {
        printQueue(q);
        currentVertex = dequeue(q);
        printf("Visited %d\n", currentVertex);
        temp = graph->adjLists[currentVertex];
        while(temp)
        {
            adjVertex = temp->vertex;
            if(graph->visited[adjVertex] == 0)
            {
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
       }
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
 

t_graph *createGraph(int vertices)
{
    t_graph *graph;
    int i;

    graph = malloc(sizeof(t_graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(t_node*));
    graph->visited = malloc(vertices * sizeof(int));
    i = 0;
    while (i < vertices)
    {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
        i++;
    }
    return graph;
}
 
void addEdge(t_graph *graph, int src, int dest)
{
    // Add edge from src to dest
    t_node *newNode;

    newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
 
    // Add edge from dest to src
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

t_queue* createQueue() {
    t_queue* q;

    q = malloc(sizeof(t_queue));
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

void enqueue(t_queue* q, int value)
{
    if(q->rear == SIZE-1)
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