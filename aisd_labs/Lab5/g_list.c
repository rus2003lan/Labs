#include "graph.h"

List *create_list() {
	return (List*) calloc(1, sizeof(List));
}

int delete_item(List *list, char *name) { 
	if (list->head == NULL) return 1;
	if (strcmp(list->head->name, name) == 0) {
		Item *tmp = list->head;
		free(tmp->name);
		list->head = list->head->next;
		free(tmp);
		return 0;
	}
	Item *ptr = list->head;
	while(ptr->next != NULL && strcmp(ptr->next->name, name) != 0) {
		ptr = ptr->next;
	}
	if (ptr->next == NULL) return 1;
	Item *tmp = ptr->next;
	ptr->next = ptr->next->next;
	free(tmp->name);
	free(tmp);
	return 0;
}

int push_list(List *list, char *name) { 
	Item *new_item;
	Item *ptr = list->head;
	if (ptr == NULL) {
		new_item = (Item *) calloc(1, sizeof(Item));
		new_item->name = name;
		list->head = new_item;
		return 0;
	}
	else {
		if (strcmp(name, ptr->name) == 0) {
			return 1;
		}
		while(ptr->next != NULL) {
			if (strcmp(name, ptr->name) == 0) {
				return 1;
			}
			ptr = ptr->next;
		}
	}
	new_item = (Item *) calloc(1, sizeof(Item));
	new_item->name = name;
	ptr->next = new_item;
	return 0;
}

void erase_list(List *list) {
	while(list->head != NULL) {
		Item *tmp = list->head;
		free(tmp->name);
		list->head = list->head->next;
		free(tmp);
	}
	free(list);
}