#include <stdio.h>
#include <stdlib.h>

typedef struct Item{
	float elem;
	struct Item* next;
}Item;

typedef struct List{
	Item* head;
}List;

List *create_list();
float *pop_list(List *);
int push_list(List *, float);
void erase_list(List *);