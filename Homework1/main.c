#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

int main(int argc, char** argv){

	//Error checks number of arguments;
	if (argc != 2){
		printf("Incorrect number of arguments! Must include file in input\n");
		return 1;
	}

	//Scans file and error checks existence of input file
	FILE* input = fopen(argv[1], "r");
	if(input == NULL){
		printf("File not found\n");
		return 1;
	}
	
	//Scans first line of file to find the number of vertices
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

		//Places destinations into correct vertexes
		int vertex, destination;
		while(token != NULL)
		{
			sscanf(token, "(%d,%d)", &vertex, &destination);			
			list[vertex-1] = createList(list[vertex-1], destination-1);
			token = strtok(NULL, " \n\r\t");
		}
	}
	
	// Prints adjacency list
	printList(list, vertices);
	
	//Stores the distances of each node from 1
	printf("\nDistances:\n");
	int* distances = BFS(vertices, list);
	
	//Prints the distances from 1
	for(i=0; i<vertices; i++){
		if(distances[i] == -1)
			printf("The distance from %d to 1 is infinity\n", i+1);
		else
			printf("The distance from %d to 1 is %d\n", i+1, distances[i]);
	}
	
	//Gives start and end times
	int* start = malloc(sizeof(int)*vertices);
	Times* end = malloc(sizeof(Times)*vertices);
	DFS(list, vertices, 0, &start, &end);
	
	/*printf("\nStart and end times:\n");
	for(i=0; i<vertices; i++){
		printf("start time of %d is %d\n", i+1, start[i]);
		printf("end time of %d is %d\n", i+1, end[i].end);
	}
	
	
	int begin;
	SCC(list, vertices, start, end);
	*/
	close(input);
	
	return 0;
}

//Creates a new node for each destination within a linked list
List* createList(List* list, int destination){
	if(list == NULL){
		List* newNode = malloc(sizeof(List));
		newNode->vertex = destination;
		newNode->next = NULL;
		return newNode;
	}
	
	list->next = createList(list->next, destination);
	return list;
}