#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

int main(int argc, char** argv){

	//Reads in file containing weighted graph
	char string[15];
	printf("Enter file name: ");
	scanf("%s", &string);
	
	//Scans file and error checks existence of input file
	FILE* input = fopen(string, "r");
	if(input == NULL){
		printf("File not found\n");
		return 1;
	}
	
	//Scans first line to determine type of graph
	char type[10];
	fscanf(input, "%s", type);
	
	//Scans second line of file to find the number of vertices
	int vertices;
	fscanf(input, "%d", &vertices);
		
	//creates array of linked lists
	List* list[vertices];
	int i;
	for(i=0; i<vertices; i++){
		list[i] = NULL;
	}
	
	//scans file and places information into linked lists
	char buffer[MAX_LINE_SIZE];
	char* token;
	while(fgets(buffer, MAX_LINE_SIZE, input))
	{
		//Error checking
		if(buffer[strlen(buffer)-1] == '\n')
			buffer[strlen(buffer)-1] = '\0';
			
		//Skips tabs, new lines, and spaces
		token = strtok(buffer, " \n\r\t");
			
		//Places destinations into correct vertices
		int vertex, destination, weight;
		while(token != NULL)
		{
			sscanf(token, "(%d,%d,%d)", &vertex, &destination, &weight);
			list[vertex-1] = createList(list[vertex-1], destination-1, weight);
			
			if(strncmp(type, "UNDIRECTED", 10) == 0){
				list[destination - 1] = createList(list[destination-1], vertex-1, weight);
			}
			
			token = strtok(NULL, " \n\r\t");
		}
	}

	// Prints adjacency list
	printList(list, vertices);
	
	if(strncmp(type, "DIRECTED", 10) == 0){
		
		printf("\nDistances:\n");
		dijkstra(vertices, list);
	}
	else if(strncmp(type, "UNDIRECTED", 10) == 0){
		
		SCC* scc = NULL;
		int graphCount =0;
		int* visited = malloc(sizeof(int)*vertices);
		visited = setVisited(visited, vertices);
		for(i=0; i<vertices; i++){
			if(visited[i] == 2){
				visited = DFS(list, i, vertices);
				scc = createVisited(scc, visited);
				graphCount++;
			}
		}
		
		if(graphCount > 1)
			printf("The graph as a whole is not strongly connected\n");
		else
			printf("The graph is strongly connected\n");
			
		//Prints the strongly connected components of the graph
		printSCC(scc, vertices);
		
		printf("\n");
		
		if(graphCount == 1)
			prim(vertices, list);
			
		free(visited);
	}
	
	close(input);
	
	return 0;
}

//Creates a new node for each destination within a linked list
List* createList(List* list, int destination, int weight){
	if(list != NULL){
		if(list->vertex == destination && list->weight >= weight){
			list->weight = weight;
			return list;
		}
	}
	
	if(list == NULL){
		List* newNode = malloc(sizeof(List));
		newNode->vertex = destination;
		newNode->next = NULL;
		newNode->weight = weight;
		return newNode;
	}
	
	list->next = createList(list->next, destination, weight);
	return list;
}