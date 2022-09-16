#include <stdio.h>
#include <stdlib.h>

typedef struct Line {
	int qty_elem;
	int *elem;
} Line;

typedef struct Matrix {
	int qty_lines;
	Line *lines;
} Matrix;

int input(Matrix *);
void output(Matrix); 
void erase(Matrix *); 
//int input_i(Matrix *); 
void result(Matrix *);
int stdin_clear();

int stdin_clear() {
	char tmp;
	int i = 0;
	while (scanf("%1[^\n]", &tmp) == 1) i++;
	if(i != 0) return 1;
	scanf("%*c");
	return 0;
}

int input(Matrix *matrix) {
	printf("Enter quantity of lines: ");
	int check = 0;
	while(check == 0) {
		(*matrix).qty_lines = 0;
		check = scanf("%d", &((*matrix).qty_lines));
		if (check == 0 || (*matrix).qty_lines < 0) {
			stdin_clear();
			printf("Error, repeat input: ");
			check = 0;
		}
		else if (check == -1) {
			return 1;
		}
		else {
			if (stdin_clear() == 1) {
				printf("Error, repeat input: ");
				check = 0;
			}
		}
	}
	int qty_lines = matrix->qty_lines;
	if(matrix->qty_lines == 0) {
		return 1;
	}
	matrix->lines = (Line *) malloc(qty_lines * sizeof(Line));
	for(int i = 1; i <= qty_lines; i++) { 
		int k = i - 1;
		printf("Enter quantity of elements per line %d: ", i);
		int check_i = 0;
		while(check_i == 0) {
			(matrix->lines + k)->qty_elem = 0;
			check_i = scanf("%d", &((matrix->lines + k)->qty_elem));
			if (check_i == 0 || (matrix->lines + k)->qty_elem < 0) {
				stdin_clear();
				printf("Error, repeat input: ");
				check_i = 0;
			}
			else if (check_i == -1) {
				matrix->qty_lines = i;
				(matrix->lines + k)->qty_elem = -1;
				return 1;
			}
			else {
				if (stdin_clear() == 1) {
					printf("Error, repeat input: ");
					check_i = 0;
				}
			}
		}
		int qty_elem = ((*matrix).lines + k)->qty_elem;
		(matrix->lines + k)->elem = (int *) malloc(qty_elem * sizeof(int));
		if (qty_elem != 0) {
			printf("Enter elements in matrix line #%d: \n", i);
		}
		for(int j = 1; j <= qty_elem; j++) {
			int m = j - 1;
			int check_j = 0;
			while(check_j == 0) {
				check_j = scanf("%d", (matrix->lines + k)->elem + m);
				if (check_j == 0) {
					stdin_clear();
					printf("Error, repeat input: ");
					check_j = 0;
				}
				else if (check_j == -1) {
					matrix->qty_lines = i;
					(matrix->lines + i - 1)->qty_elem = m;
					return 1;
				}
				else {
					if (stdin_clear() == 1) {
						printf("Error, repeat input: ");
						check_j = 0;
					}
				}
			}
		}
	}
	printf("\n\n");
}

void erase(Matrix *matrix) {
	for(int i = 1; i <= matrix->qty_lines; i++) {
		int k = i - 1;
		if ((matrix->lines + k)->qty_elem != -1) free((matrix->lines + k)->elem);
	}
	if(matrix->qty_lines != 0) free(matrix->lines);
}

void output(Matrix matrix) {
	for(int number_line = 1; number_line <= matrix.qty_lines; number_line++) {
		int i = number_line - 1;
		for(int number_elem = 1; number_elem <= (matrix.lines + i)->qty_elem; number_elem++) {
			int j = number_elem - 1;
			printf("%d ", *(((matrix.lines + i)->elem) + j));
		}
		printf("\n");
    }
    printf("\n");
}

/*int input_i(Matrix *matrix) {
	if(matrix->qty_lines != 0) {
		printf("Enter line number for changes: \n");
		int check = 0;
		while(check == 0) {
			int i = matrix->qty_lines;
			check = scanf("%d", &i);
			if (check == 0 ||  i <= 0 || i > matrix->qty_lines) {
				stdin_clear();
				printf("Error, repeat input: ");
				check = 0;
			}
			else if (check == -1) {
				return 0;
			}
			else {
				if (stdin_clear() == 1) {
					printf("Error, repeat input: ");
					check = 0;
				}
				else return i;
			}
		}
		printf("\n\n");
	}
}*/

void result(Matrix *matrix) {
	for(int i = 0; i < matrix->qty_lines; i++) {
		int new_qty = 0;
		int *ptr = (matrix->lines + i)->elem;
		for(int j1 = 0; j1 < (matrix->lines + i)->qty_elem; j1++) {
			int *elem1 = (matrix->lines + i)->elem + j1; 
			for(int j2 = 0; j2 < (matrix->lines + i)->qty_elem; j2++) {
				int *elem2 = (matrix->lines + i)->elem + j2;
				if (j1 == j2) continue;
				else if(*elem1 == *elem2) {
					*ptr = *elem1;
					ptr++;
					new_qty++;
					break;
				}
			}
		}
		int *new_elem = (int*) malloc(new_qty * sizeof(int));
		for(int j = 0; j < new_qty; j++){
			new_elem[j] = (matrix->lines + i)->elem[j];
		}
		if ((matrix->lines + i)->qty_elem != 0) {
			free((matrix->lines + i)->elem);
			(matrix->lines + i)->elem = (int*) malloc(new_qty * sizeof(int));
		}
		for(int j = 0; j < new_qty; j++){
			(matrix->lines + i)->elem[j] = new_elem[j];
		}
		(matrix->lines + i)->qty_elem = new_qty;
		free(new_elem);
	}
}