#include <stdio.h>
#include <stdlib.h>

#include "header.h"

/*
	Determines the strongly connected components given a node of the graph
	returns the visited array containing the strongly connected components
*/
int* DFS(List** list, int pointer, int numberOfVertices){

	int* visited = malloc(sizeof(int) * numberOfVertices);
		
	//visited of each node is set to undiscovered (2)
	visited = setVisited(visited, numberOfVertices);

	DFS_Visit(list, pointer, &visited);
	
	return visited;
}

//Visits the nodes and change visited to "1"
void DFS_Visit(List** list, int pointer, int** visited){
	(*visited)[pointer] = 1;
	
	List* key = list[pointer];
	while(key != NULL){		
		if((*visited)[key->vertex] == 2){	
			DFS_Visit(list, key->vertex, visited);
		}
		
		key = key->next;
	}
}

/*
	Creates a new SCC by inserting a visited array into the structure
*/
SCC* createVisited(SCC* scc, int* visited){
	if(scc == NULL){
		SCC* newArray = malloc(sizeof(SCC));
		newArray->visited = visited;
		newArray->next = NULL;
		return newArray;
	}
	
	scc->next = createVisited(scc->next, visited);
	return scc;
}

/*
	Sets all elements in the array to unvisited
*/
int* setVisited(int* visited, int vertices){
	int i;
	for(i=0; i<vertices; i++){
		visited[i] = 2;
	}
	
	return visited;
}