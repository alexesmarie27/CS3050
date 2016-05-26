#include <stdio.h>
#include <stdlib.h>

#include "header.h"

//Breadth first search that finds the distances of each node from 1
//Returns the distances array
int* BFS(int numberOfVertices, List** vertices){
	
	//the color of each node is set to undiscovered (white)
	//the distance from each node from 1 set to infinity
	int* distances = malloc(sizeof(int) * numberOfVertices);
	char colors[numberOfVertices];
	int i;
	for(i=1; i<numberOfVertices; i++){
		distances[i] = -1;
		colors[i] = 'w';
	}	
	
	//Sets beginning vertex 1 as distance 0, color grey
	distances[0] = 0;
	colors[0] = 'g';

	//Enqueues the vertex
	List* queue = enqueue(NULL, 0);
	
	//holdingQ acts as a means for knowing when one level is done so the distance counter can be bumped
	//while the queue is not null, the program continues searching for adjacent nodes
	//when each node is found, its color is changed to discovered(grey) and its distance is stored in the distances array
	List* holdingQ = malloc(sizeof(List));
	int distance =1;
	while(holdingQ != NULL){
		holdingQ = NULL;
	
		while(queue != NULL){
			List* current = dequeue(&queue);
			List* list = vertices[current->vertex];
			
			while(list != NULL){
				if(colors[list->vertex] == 'w'){
					colors[list->vertex] = 'g';
					holdingQ = enqueue(holdingQ, list->vertex);
					distances[list->vertex] = distance;
				}		
				list= list->next;
			}	
		}
		
		distance++;
		queue = holdingQ;
	}
	
	return distances;
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