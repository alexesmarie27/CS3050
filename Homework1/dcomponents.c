#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

//prints an adjacency list
void printComponents(int* components){	
	printf("ergegv\n");
	int counter = 0;
	while(components[counter] != 0){
		printf("%d ", components[counter]);
	}
}