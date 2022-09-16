#include <stdio.h>
#include "functions.h"

int main() {
	Matrix matrix;
	int check = input(&matrix);
	printf("\n\n");
	output(matrix);
	if (check != 1) {
		result(&matrix);
		output(matrix);
	}
	erase(&matrix);
	return 0;
}