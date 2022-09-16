#include "stack.h"

Stack *create(int qty_elem) {
	Stack *stack = (Stack*) malloc(sizeof(Stack));
	stack->data.vector = create_vector(qty_elem);
	stack->top = 0;
	return stack;
}

float *pop(Stack *stack) {
	int top = stack->top - 1;
	float *elem = pop_vector(stack->data.vector, top);
	if (top != -1) (stack->top)--;
	return elem;
}

int push(Stack *stack, float elem) {
	int check = push_vector(stack->data.vector, stack->top, elem);
	(stack->top)++;
	return check;
}

void erase(Stack *stack) {
	erase_vector(stack->data.vector);
	free(stack);
}


void erase_after_pop(float *elem) {
}