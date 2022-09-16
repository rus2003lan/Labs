#include "list.h"

List *create_list() {
	return (List*) calloc(1, sizeof(List));
}

float *pop_list(List *list) {
	if (list->head != NULL) {
		float *element = (float *) malloc(sizeof(float));
		*element = list->head->elem;
		Item *tmp = list->head;
		list->head = list->head->next;
		free(tmp);
		return element;
	}
	return NULL;
}

int push_list(List *list, float element) { 
	Item *new_head = (Item *) malloc(sizeof(Item));
	new_head->next = list->head;
	new_head->elem = element;
	list->head = new_head;
	return 0;
}

void erase_list(List *list) {
	while(list->head != NULL) {
		Item *tmp = list->head;
		list->head = list->head->next;
		free(tmp);
	}
	free(list);
}