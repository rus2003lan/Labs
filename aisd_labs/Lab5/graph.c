#include "graph.h"

Graph *create_graph() {
	Graph *graph = (Graph *) calloc(1, sizeof(Graph));
	Vertex *new_vertices = (Vertex *) calloc(50, sizeof(Vertex));
	graph->vertices = new_vertices;
	graph->max_size = 50;
	return graph;
}

int add_vertex(Graph *graph, char *name) {
    if (graph->max_size == graph->qty_vertices) {
        graph->max_size *= 2;
        graph->vertices = realloc(graph->vertices, graph->max_size * sizeof(Vertex));
    }
    int index = 0;
    while (index < graph->qty_vertices) {
        if (strcmp(name, (graph->vertices + index)->name) == 0) {
            return 1;
        }
        ++index;
    }
    List *new_list = create_list();
    (graph->vertices + index)->edges = new_list;
    (graph->vertices + index)->name = name;
    ++graph->qty_vertices;
    return 0;
}

int add_edge(Graph *graph, char *name1, char *name2) {
	int index = 0;
	int index1;
	int flag;
	int check;
	while(index < graph->qty_vertices) {
		if (strcmp((graph->vertices + index)->name, name1) == 0) {
			flag = 1;
			break;
		}
		if (strcmp((graph->vertices + index)->name, name2) == 0) {
			flag = 2;
			break;
		}
		++index;
	}
	if (index == graph->qty_vertices) return 1; // ни одной вершины нет
	index1 = index + 1;
	if (flag == 1) {
		while(index1 < graph->qty_vertices) {
			if (strcmp((graph->vertices + index1)->name, name2) == 0) break;
			++index1;
		}
		if (index1 == graph->qty_vertices) return 1; // нет 2 вершины
		check = push_list((graph->vertices + index)->edges, name2);
		if (check == 1) return 2;
		check = push_list((graph->vertices + index1)->edges, name1);
		if (check == 1) return 2;
	}
	else if (flag == 2) {
		while(index1 < graph->qty_vertices) {
			if (strcmp((graph->vertices + index1)->name, name1) == 0) break;
			++index1;
		}
		if (index1 == graph->qty_vertices) return 1; // нет 1 вершины
		check = push_list((graph->vertices + index)->edges, name1);
		if (check == 1) return 2;
		check = push_list((graph->vertices + index1)->edges, name2);
		if (check == 1) return 2;
	}
	return 0;
}

int delete_edge(Graph *graph, char *name1, char *name2) {
	int index1 = index_name(graph, name1);
	int index2 = index_name(graph, name2);
	if (index1 == -1 || index2 == -1) return 1;
	int check = delete_item((graph->vertices + index1)->edges, name2);
	if (check == 1) return 2;
	check = delete_item((graph->vertices + index2)->edges, name1);
	if (check == 1) return 2;
	return 0;
}

int delete_vertex(Graph *graph, char *name) {
	if (graph == NULL) return 1;
	int i = 0;
	for(i; i < graph->qty_vertices; ++i) {
		if (strcmp(name, (graph->vertices + i)->name) == 0) {
			break;
		}
	}
	if (i == graph->qty_vertices) return 1;
	Item *ptr = (graph->vertices + i)->edges->head;
	char *now_name;
	while (ptr != NULL) {
		now_name = ptr->name;
		for (int j = 0; j < graph->qty_vertices; ++j) {
			if (strcmp(now_name, (graph->vertices + j)->name) == 0) {
				delete_item((graph->vertices + j)->edges, name);
				break;
			}
		}
		ptr = ptr->next;
	}
	erase_list((graph->vertices + i)->edges);
	free((graph->vertices + i)->name);
	(graph->vertices + i)->name = (graph->vertices + (graph->qty_vertices - 1))->name;
	(graph->vertices + i)->edges = (graph->vertices + (graph->qty_vertices - 1))->edges;
	--graph->qty_vertices;
	return 0;
}

void erase(Graph *graph) {
	for(int i = 0; i < graph->qty_vertices; ++i) {
		free((graph->vertices + i)->name);
		erase_list((graph->vertices + i)->edges);
	}
	free(graph->vertices);
	free(graph);
}

void show(Graph *graph) {
	if (graph != NULL) {
		Item *ptr;
		for(int i = 0; i < graph->qty_vertices; ++i) {
			printf("%s: ", (graph->vertices + i)->name);
			ptr = (graph->vertices + i)->edges->head;
			while(ptr != NULL) {
				printf("%s, ", ptr->name);
				ptr = ptr->next;
			}
			printf("\n");
		}
	}
}

int bfs(Graph *graph, char *name1, char *name2) {
	int index1 = index_name(graph, name1);
	int index2 = index_name(graph, name2);
	if (index1 == -1 || index2 == -1) return -1;
	int color[graph->qty_vertices];   // белый 0; серый 1; черный 2;
	int d[graph->qty_vertices];
	char *pred[graph->qty_vertices];
	for (int i = 0; i < graph->qty_vertices; ++i) {
		color[i] = 0;
		d[i] = INT_MAX;
		pred[i] = NULL;
	}
	color[index1] = 1;
	d[index1] = 0;
	Queue *queue = create_queue();
	push_queue(queue, name1);
	char *u;
	int index3, index;
	Item *ptr;
	while (isempty(queue) != 0) {
		pop_queue(queue, &u);
		index3 = index_name(graph, u);
		ptr = (graph->vertices + index3)->edges->head;
		while (ptr != NULL) {
			index = index_name(graph, ptr->name);
			if (color[index] == 0) {
				color[index] = 1;
				d[index] = d[index3] + 1;
				pred[index] = u;
				push_queue(queue, ptr->name);
			}
			ptr = ptr->next;
		}
		color[index3] = 2;
	}
	erase_queue(queue);
	print_path(graph, name1, name2, pred);
	return 0;
}

int dijkstra(Graph *graph, char *name1, char *name2) {
	int index1 = index_name(graph, name1);
	int index2 = index_name(graph, name2);
	if (index1 == -1 || index2 == -1) return -1;
	int d[graph->qty_vertices];
	char *pred[graph->qty_vertices];
	for (int i = 0; i < graph->qty_vertices; ++i) {
		d[i] = INT_MAX;
		pred[i] = NULL;
	}
	d[index1] = 0;
	Queue *queue = create_queue();
	push_queue(queue, name1);
	char *u;
	int index3, index;
	Item *ptr;
	while (isempty(queue) != 0) {
		pop_queue(queue, &u);
		index3 = index_name(graph, u);
		ptr = (graph->vertices + index3)->edges->head;
		while (ptr != NULL) {
			index = index_name(graph, ptr->name);
			if (d[index] > d[index3] + 1) {
				d[index] = d[index3] + 1;
				pred[index] = u;
				push_queue(queue, ptr->name);
			}
			ptr = ptr->next;
		}
	}
	erase_queue(queue);
	print_path(graph, name1, name2, pred);
	return 0;
}

void print_path (Graph *graph, char *name1, char *name2, char **pred) {
	int index;
	if (strcmp(name1, name2) == 0) {
		printf("%s ", name1);
	}
	else {
		index = index_name(graph, name2);
		if (pred[index] == NULL) {
			printf("No path");
		}
		else {
			print_path(graph, name1, pred[index], pred);
			printf("%s ", name2);
		}
	}
}

int index_name(Graph *graph, char *name) {
	if (graph == NULL) return -1;
	for (int i = 0; i < graph->qty_vertices; ++i) {
		if (strcmp(name, (graph->vertices + i)->name) == 0) {
			return i;
		}
	}
	return -1;
}