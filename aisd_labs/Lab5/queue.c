#include "graph.h"

int isempty(Queue *queue) {
	if (queue->head == NULL) return 0;
	else return 1;
}

Queue *create_queue() {
	return (Queue *) calloc(1, sizeof(Queue));
}

int pop_queue(Queue *queue, char **name) {
	if (queue->head != NULL) {
		int flag = 0;
		if (queue->head == queue->tail) flag = 1;
		*name = queue->head->name;
		Item *tmp = queue->head;
		queue->head = queue->head->next;
		if (flag == 1) queue->tail = NULL;
		free(tmp);
		return 0;
	}
	return 1;
}

int push_queue(Queue *queue, char *name) { 
	Item *new_item = (Item *) calloc(1, sizeof(Item));
	new_item->name = name;
	if (queue->head == NULL) {
		queue->head = new_item;
		queue->tail = new_item;
		return 0;
	} 
	queue->tail->next = new_item;
	queue->tail = new_item;
	return 0;
}

void erase_queue(Queue *queue) {
	while(queue->head != NULL) {
		Item *tmp = queue->head;
		queue->head = queue->head->next;
		free(tmp);
	}
	free(queue);
}