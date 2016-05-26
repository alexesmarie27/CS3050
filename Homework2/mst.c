#include <stdio.h>
#include <stdlib.h>

#include "header.h"

/*
	Prim's algorithm is used to create a min spanning tree
	Each node (except for the root) is set to 2 meaning unvisited
	Goes through each visited node and checks for the smallest weight connected to a visited node
	When the smallest is found, that edge is added to the edges array
	Prints the edges
*/
void prim(int numberOfVertices, List** vertices){
	
	//1 == true
	//2 == false
	int* visited = malloc(sizeof(int) * numberOfVertices);
	visited[0] = 1;
	int i;
	for(i=1; i<numberOfVertices; i++){
		visited[i] = 2;
	}
	
	Edge* edges = malloc(sizeof(Edge) * (numberOfVertices-1));	
	
	int edgeCount = 0;
	while(edgeCount < (numberOfVertices - 1)){
		int min = 1000;
		int minIndex = 0;
		int vertex = 0;
		
		for(i=0; i<numberOfVertices; i++){
			if(visited[i] == 1)
			{
				List* list = vertices[i];
				
				while(list != NULL){
				
					if(visited[list->vertex] == 2 && min >list->weight){
						vertex = i+1;
						min = list->weight;
						minIndex = (list->vertex);
					}
					
					list = list->next;
				}
			}
		}
		
		Edge newEdge = createEdge(vertex, minIndex, min);
		visited[minIndex] = 1;
		edges[edgeCount] = newEdge;
		edgeCount++;
	}
	
	printPrim(numberOfVertices, edges);
}

/*
	Creates a new edge by inserting a vertex (the vertex the path is going from), a destination(the vertex the path is going to), and a weight
*/
Edge createEdge(int vertex, int minIndex, int minWeight){
	Edge newEdge;
	newEdge.vertex = vertex;
	newEdge.destination = minIndex + 1;
	newEdge.weight = minWeight;
	return newEdge;
}

/*
	Prints the edges of the MST
*/
void printPrim(int numberOfVertices, Edge* edges){
	int i;
	for(i=0; i<numberOfVertices-1; i++){
		if(edges[i].weight == 1000)
			printf("The edge added between %d and %d is of weight infinity\n", edges[i].vertex, edges[i].destination);
		else
			printf("The edge added between %d and %d is of weight %d\n", edges[i].vertex, edges[i].destination, edges[i].weight);
	}
}

/*
	Prints each group of strongly connected components
*/
void printSCC(SCC* scc, int vertices){
	int counter = 1;
	while(scc != NULL){
	
		printf("Strongly Connected Group %d: ", counter++);
		
		int i;
		for(i=0; i<vertices; i++){
			if(scc->visited[i] == 1){
				printf(" %d ", i+1);
			}
		}
		printf("\n");
		scc = scc->next;
	}
}