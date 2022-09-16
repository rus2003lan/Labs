#include "vector.h"

Vector *create_vector(int qty_elem) {
	Vector *vector = (Vector*) malloc(sizeof(Vector));
	vector->elem = (float *) malloc(qty_elem * sizeof(float));
	vector->busy = (char *) calloc(qty_elem, sizeof(char));
	vector->qty_elem = qty_elem;
	return vector;
}

float *pop_vector(Vector *vector, int index) {
	if (vector->qty_elem > index && index >= 0) {
		if (*(vector->busy + index) == 1) {
			*(vector->busy + index) = 0;
			return vector->elem + index;
		}
	}
	return NULL;
}

int push_vector(Vector *vector, int index, float elem) {
	if (vector->qty_elem > index && index >= 0) {
		if (*(vector->busy + index) == 0) {
			*(vector->elem + index) = elem;
			*(vector->busy + index) = 1;
			return 0;
		return 1;
		}
	}
	return -1;
}

void erase_vector(Vector *vector) {
	free(vector->elem);
	free(vector->busy);
	free(vector);
}