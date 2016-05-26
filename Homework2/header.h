#define MAX_LINE_SIZE 100

//Structure for linked list
typedef struct list_{
	int vertex;
	int weight;
	struct list_* next;
}List;

//Structure for edges
typedef struct edge_{
	int vertex;
	int destination;
	int weight;
}Edge;

//Structure for the strongly connected components
typedef struct scc_{
	int* visited;
	struct scc_* next;
}SCC;


//Prototypes
List* createList(List* list, int destination, int weight);
void prim(int numberOfVertices, List** vertices);
void dijkstra(int numberOfVertices, List** vertices);
List* enqueue(List* queue, int vertex);
List* dequeue(List** queue);
void printList(List** list, int vertices);
Edge createEdge(int vertex, int minIndex, int minWeight);
int* DFS(List** list, int pointer, int numberOfVertices);
void DFS_Visit(List** list, int pointer, int** visited);
SCC* createVisited(SCC* scc, int* visited);
int* setVisited(int* visited, int vertices);
void printDijkstra(int* distances, int numberOfVertices);
void printPrim(int numberOfVertices, Edge* edges);
void printSCC(SCC* scc, int vertices);
