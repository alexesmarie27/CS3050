#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

//prints an adjacency list
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
}