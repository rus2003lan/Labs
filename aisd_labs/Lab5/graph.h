#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Item {
	char *name;
	struct Item* next;
} Item;

typedef struct List {
	Item* head;
} List;

typedef struct Vertex {
	List *edges;
	char *name;
} Vertex;

typedef struct Graph {
	Vertex *vertices;
	int qty_vertices;
	int max_size;	
} Graph;

typedef struct Queue {
	Item *head;
	Item *tail;
} Queue;

int push_queue(Queue *queue, char *name);
int pop_queue(Queue *queue, char **name);
Queue *create_queue();
void erase_queue(Queue *queue);
int isempty(Queue *queue);
void menu();
Graph *create_graph();
List *create_list();
int delete_item(List *list, char *name);
int push_list(List *list, char *name);
void erase_list(List *list);
int add_vertex(Graph *graph, char *name);
int add_edge(Graph *graph, char *name1, char *name2);
void erase(Graph *graph);
void show(Graph *graph);
int delete_vertex(Graph *graph, char *name);
int delete_edge(Graph *graph, char *name1, char *name2);
char *get_str();
int stdin_clear();
int getint(int *number);
int bfs(Graph *graph, char *name1, char *name2);
int index_name(Graph *graph, char *name);
void print_path(Graph *graph, char *name1, char *name2, char **pred);
int dijkstra(Graph *graph, char *name1, char *name2);