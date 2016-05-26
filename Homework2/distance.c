#include <stdio.h>
#include <stdlib.h>

#include "header.h"

/*
	Dijkstra: finds the shortest distances of each node from 1
	If a distance is changed, it is enqueued into the queue
	Prints the distances of each node from 1
*/
void dijkstra(int numberOfVertices, List** vertices){

	int* distances = malloc(sizeof(int) * numberOfVertices);

	distances[0] = 0;
		
	List* queue = malloc(sizeof(List));
	queue = enqueue(NULL, 0);
	
	//the distance from each node from 1 set to infinity (infinty == 10000)
	int i;
	for(i=1; i<numberOfVertices; i++){
		distances[i] = 10000;
	}	
	
	while(queue != NULL){
			
		List* current = dequeue(&queue);
			
		List* list = vertices[current->vertex];
		
		while(list != NULL){
			if(list->weight + distances[current->vertex] < distances[list->vertex]){
				distances[list->vertex] = list->weight + distances[current->vertex];
				queue = enqueue(queue, vertices[current->vertex]->vertex);
			}

			list = list->next;
		}
	}
	
	printDijkstra(distances, numberOfVertices);
}

//Adds nodes to the linked list
//Returns the updated queue
List* enqueue(List* queue, int vertex){

	List* pointer  = queue;
	
	if(queue == NULL){
		pointer = malloc(sizeof(List));
		pointer->vertex = vertex;
		pointer->next = NULL;
		return pointer;
	}

	queue->next = enqueue(pointer->next, vertex);
	return queue;
}

//Removes nodes from the beginning of the linked list
//Returns the dequeued node
List* dequeue(List** queue){

	if((*queue) == NULL){
		printf("Invalid. Queue is empty!\n");
		return NULL;
	}

	List* deQNode = (*queue);
	*queue = (*queue)->next;

	return deQNode;
}

/*
	Prints the distances of each vertex from vertex 1
*/	
void printDijkstra(int* distances, int numberOfVertices){
	int i;
	for(i=0; i<numberOfVertices; i++){
		if(distances[i] == 10000)
			printf("The distance from 1 to %d is infinity\n", i+1);
		else
			printf("The distance from 1 to %d is %d\n", i+1, distances[i]);
	}
}