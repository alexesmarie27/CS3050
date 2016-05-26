#define MAX_LINE_SIZE 100

//Structure for linked list
typedef struct list_{
	int vertex;
	struct list_* next;
}List;

//Structure to keep track of end times
typedef struct times_{
	int vertex;
	int end;
}Times;

//Prototypes
List* createList(List* list, int destination);
void printList(List** list, int vertices);
List* dequeue(List** queue);
int* BFS(int numberOfVertices, List** vertices);
List* enqueue(List* queue, int vertex);
void DFS_Visit(List** vertices, int pointer, char** colors, int** start, Times** end, int* time);
void DFS(List** vertices, int numberOfVertices, int begin, int** start, Times** end);
List** transpose(List** list, int numberOfVertices);
Times* sortEndTimes(Times* times, int numberOfVertexes);
void printComponents(int* components);