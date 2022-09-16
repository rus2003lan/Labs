#include "stack.h"

Stack *create(int a) {
	Stack *stack = (Stack *) malloc(sizeof(Stack));
	stack->data.list = create_list();
	return stack;
}

float *pop(Stack *stack) {
	float *elem = pop_list(stack->data.list);
	return elem;
}

int push(Stack *stack, float elem) {
	push_list(stack->data.list, elem);
	return 0;
}

void erase(Stack *stack) {
	erase_list(stack->data.list);
	free(stack);
}


void erase_after_pop(float *elem) {
	free(elem);
}