#include "list.h"
#include "vector.h"

union Union {
	Vector *vector;
	List *list;
};

typedef struct Stack {
	int top;
	union Union data;
} Stack;

float *pop(Stack *);
int push(Stack *, float);
Stack *create(int);
void erase(Stack *);
void erase_after_pop(float *);