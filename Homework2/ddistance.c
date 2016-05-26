#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

/*
	Prints the adjacency list of each vertex in the graph
*/
void printList(List** list, int vertices){	
	
	printf("\nAdjacency list: \n");
	
	int i;
	for(i=0; i<vertices; i++){
		List* pointer = list[i];
		
		printf("%d: ", i+1);
		
		while(pointer != NULL){
			printf("%d -> ", pointer->vertex+1);
			pointer = pointer->next;
		}
		
		printf("End\n");
	}
	
	printf("\n");
}