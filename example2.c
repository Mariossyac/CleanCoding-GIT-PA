#include <stdio.h>
#include <stdlib.h>

// Definirea structurii pentru lista de adiacență
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Definirea structurii pentru graf
typedef struct Graph {
    int vertices;
    int *visited;
    Node **adjList;
} Graph;

// Funcție pentru crearea unui nod nou
Node *createNode(int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        printf("Eroare la alocarea memoriei!\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Funcție pentru crearea grafului
Graph *createGraph(int vertices) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (!graph) {
        printf("Eroare la alocarea memoriei!\n");
        exit(EXIT_FAILURE);
    }
    graph->vertices = vertices;
    graph->adjList = (Node **)malloc(vertices * sizeof(Node *));
    graph->visited = (int *)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

// Funcție pentru adăugarea unei muchii
void addEdge(Graph *graph, int src, int dest) {
    Node *newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// Funcție pentru parcurgerea DFS
void DFS(Graph *graph, int vertex) {
    graph->visited[vertex] = 1;
    printf("%d -> ", vertex);

    Node *temp = graph->adjList[vertex];
    while (temp) {
        int connectedVertex = temp->data;
        if (!graph->visited[connectedVertex]) {
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

// Funcție pentru parcurgerea BFS
void BFS(Graph *graph, int start) {
    int queue[graph->vertices], front = 0, rear = 0;
    graph->visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int currentVertex = queue[front++];
        printf("%d -> ", currentVertex);

        Node *temp = graph->adjList[currentVertex];
        while (temp) {
            int adjVertex = temp->data;
            if (!graph->visited[adjVertex]) {
                graph->visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }
}

// Funcție pentru resetarea vizitelor
void resetVisited(Graph *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}

// Funcția principală
int main() {
    int vertices, edges, startVertex;

    printf("Numărul de noduri din graf: ");
    scanf("%d", &vertices);
    printf("Numărul de muchii: ");
    scanf("%d", &edges);

    Graph *graph = createGraph(vertices);

    printf("Introduceți muchiile (ex: 1 2 pentru muchie între nodurile 1 și 2):\n");
    for (int i = 0; i < edges; i++) {
        int src, dest;
        scanf("%d%d", &src, &dest);
        addEdge(graph, src, dest);
    }

    printf("Nodul de start pentru DFS: ");
    scanf("%d", &startVertex);
    printf("Parcurgerea DFS:\n");
    DFS(graph, startVertex);
    resetVisited(graph);

    printf("\nNodul de start pentru BFS: ");
    scanf("%d", &startVertex);
    printf("Parcurgerea BFS:\n");
    BFS(graph, startVertex);

    return 0;
}