#include <stdio.h>
#include <stdlib.h>

typedef struct Vector {
	int qty_elem;
	float *elem;
	char *busy;
} Vector;

Vector *create_vector(int);
float *pop_vector(Vector *, int);
int push_vector(Vector *, int , float);
void erase_vector(Vector *);