#include "graph.h"

void menu() {
	while (1) {
		int alternative;
		int check;
		int flag = 0;
		Graph *graph = create_graph();
		while (flag == 0) {
			printf("Choose an alternative:\n 1)BFS 2)Add edge 3)Add vertex 4)Show 5)Delete edge 6)Delete vertex 7)Dijkstra 8)Exit\n");
			check = getint(&alternative);
			if (check == 0) {
				if (alternative == 1) {
					printf("Input name of vertex 1:\n");
					char *name1 = get_str();
					printf("Input name of vertex 2:\n");
					char *name2 = get_str();
					int bfs_check = bfs(graph, name1, name2);
					printf("\n");
					if (bfs_check == -1) printf("No such vertex\n");
					free(name1);
					free(name2);
					continue;
				}
				else if (alternative == 2) {
					printf("Input name of vertex 1:\n");
					char *name1 = get_str();
					printf("Input name of vertex 2:\n");
					char *name2 = get_str();
					int add_check = add_edge(graph, name1, name2);
					if (add_check == 0) {
						printf("Insert was successful!\n");
						continue;
					}
					else if (add_check == 1) printf("No such vertex \n");
					else if (add_check == 2) printf("This edge already exists \n");
					free(name1);
					free(name2);
					continue;
				}
				else if (alternative == 3) {
					printf("Input name of vertex:\n");
					char *name = get_str();
					int add_check = add_vertex(graph, name);
					if (add_check == 0) {
						printf("Insert was successful!\n");
						continue;
					}
					else {
						printf("Error, this vertex already exists\n");
						free(name);
						continue;
					}
				}
				else if (alternative == 4) {
					printf("Graph:\n");
					show(graph);
				}
				else if (alternative == 5) {
					printf("Input name of vertex 1:\n");
					char *name1 = get_str();
					printf("Input name of vertex 2:\n");
					char *name2 = get_str();
					int del_check = delete_edge(graph, name1, name2);
					if (del_check == 0) printf("Delete was successful!\n");
					else if (del_check == 1) printf("No such vertex\n");
					else if (del_check == 2) printf("No such edge\n");
					free(name1);
					free(name2);
					continue;
				}
				else if (alternative == 6) {
					printf("Input name of vertex:\n");
					char *name = get_str();
					int del_check = delete_vertex(graph, name);
					if (del_check == 0) {
						printf("Delete was successful!\n");
					}
					else {
						printf("Error, vertex not found\n");
					}
					free(name);
					continue;
				}
				else if (alternative == 7) {
					printf("Input name of vertex 1:\n");
					char *name1 = get_str();
					printf("Input name of vertex 2:\n");
					char *name2 = get_str();
					int dijkstra_check = dijkstra(graph, name1, name2);
					printf("\n");
					if (dijkstra_check == -1) printf("No such vertex\n");
					free(name1);
					free(name2);
					continue;
				}
				else if (alternative == 8) break;
				else if (alternative > 8 || alternative < 1) {
					continue;
				}
			}
			else if (check == 1) printf("Please, repeat unput\n");
			else {
				flag = 1;
				break;
			}	
		}
	erase(graph);
	break;
	}
}

int getint(int *number) {
	int check1 = scanf("%d", number);
	int check2 = stdin_clear();
	if (check1 == -1) return -1;
	else if (check1 == 0 || check2 == 1) return 1;
	else return 0;
}

int stdin_clear() {
	char tmp;
	int i = 0;
	while (scanf("%1[^\n]", &tmp) == 1) i++;
	if(i != 0) return 1;
	scanf("%*c");
	return 0;
}

char *get_str() {
    char buf[81] = {0};  // BUFSIZ - константа для длины буфера
    char *res = NULL;
    unsigned int len = 0;
    unsigned int n = 0;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        } else if (n > 0) {
            unsigned int chunk_len = strlen(buf);
            unsigned int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
    }

    return res;
}