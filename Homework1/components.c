#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"
	
//Determines the start and end times of each node
//Used in order to find the strongly connected components
void DFS(List** vertices, int numberOfVertices, int begin, int** start, Times** end){

	int time = 1;
	char* colors = malloc(sizeof(char) * numberOfVertices);
		
	//the color of each node is set to undiscovered (white)
	//the start and end time of each node is to 0
	int i;
	for(i=0; i<numberOfVertices; i++){
		colors[i] = 'w';
		(*start)[i] = 0;
		(*end)[i].vertex = i;
		(*end)[i].end = 0;
	}	

	//For each node, visit the node and establish start and end times for that node
	for(i=0; i<numberOfVertices; i++){
		if(colors[i] == 'w')
			DFS_Visit(vertices, i, &colors, start, end, &time);
	}
}

//Visits the node and determines it's start and end times
void DFS_Visit(List** vertices, int pointer, char** colors, int** start, Times** end, int* time){

	(*start)[pointer] = (*time)++;
	(*colors)[pointer] = 'g';

	List* key = vertices[pointer];
	while(key != NULL){		
		if((*colors)[key->vertex] == 'w'){
			DFS_Visit(vertices, key->vertex, colors, start, end, time);
		}

		key = key->next;
	}
	
	(*end)[pointer].end = (*time)++;
}

//Transposes the list (reverses the lists so that if "a" pointed to "b", "b" now points to "a")
//Returns the transposed list
List** transpose(List** list, int numberOfVertices){

	List** transposed = malloc(sizeof(List*) * numberOfVertices);
	List* pointer;
	int location;
	
	int i;
	for(i=0; i<numberOfVertices; i++){
		transposed[i] = NULL;
	}
	
	for(i=0; i<numberOfVertices; i++){
		
		pointer = list[i];
		while(pointer != NULL){
			location = pointer->vertex;
			transposed[location] =  enqueue(transposed[location], i);
			
			pointer = pointer->next;
		}
	}
	
	return transposed;
}

//Sorts the end times into increasing order
//Returns the sorted end times
Times* sortEndTimes(Times* times, int numberOfVertexes){
	
	int i, j;
	for(i=0; i<numberOfVertexes; i++){
		for(j=1; j<numberOfVertexes; j++){
			if(times[j].end < times[j-1].end){
				Times temp = times[j];
				times[j] = times[j-1];
				times[j-1] = temp;
			}
		}
	}
	
	return times;
}

void SCC(List** list, int vertices, int** start, Times** end){

	DFS(list, vertices, 0, start, end);
	Times* sortedTimes = sortEndTimes(*end, vertices);
	List** transposed = transpose(list, vertices);
	int position =0;
	//Prints Strongly connected components
	while(position != vertices){
		int* tempStart = malloc(sizeof(int) * vertices);
		Times* tempEnd = malloc(sizeof(Times) * vertices);
		DFS(transposed, vertices, position, &tempStart, &tempEnd);
			
		int i;
		int strongConnect[vertices];
		for(i=0; i<vertices; i++){
			strongConnect[i] = 0;
		}
		int strongConnectCount = 0;
		for(i=position; i<vertices; i++){
			if(tempEnd[i].end != 0){
				strongConnect[strongConnectCount++] = tempEnd[i].vertex;
				position++;
			}
		}
		
		printComponents(strongConnect);
	}
	

}