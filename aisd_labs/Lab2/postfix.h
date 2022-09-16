#include "stack.h"

int result (Stack *);
int stdin_clear();
int process_sign(char, Stack *);
int f(char);

int result(Stack *stack) { 
	int check_digit = 0;
	int check_sign = 0;
	char sign;
	char char_digit;
	printf("Enter expression: \n");
	while(1) {
		check_digit = scanf("%1[0-9]", &char_digit);
		if (check_digit == 0) {
			check_sign = scanf("%c", &sign);
			if (check_sign == -1) return -1;
			int checking = process_sign(sign, stack);
		    if (checking == -1) {
		    	stdin_clear();
		    	return 1;
		    }
		    else if (checking == -2) return 0;
		}
		else if (check_digit == -1) {
			return -1;
		}
		else {
			int digit = (int)char_digit - 48;
			int check = push(stack, digit);
			if (check == -1) {
				stdin_clear();
				return 1;
			}
		}
	}
	return 0;
}

int stdin_clear() {
	char tmp;
	int i = 0;
	while (scanf("%1[^\n]", &tmp) == 1) i++;
	if(i != 0) return 1;
	scanf("%*c");
	return 0;
}

int f (char sign) {
	if (sign == '+') return 1;
    else if (sign == '-') return 2;
    else if (sign == '*') return 3;
    else if (sign == '/') return 4; 
	else if (sign == ' ') return 0;
	else if (sign == '\n') return -2;
	else return -1;
}

int process_sign (char sign, Stack *stack) {
	int g  = f(sign);
	if (g == 0) return 0;
	if (g == -1) return -1;
	if (g == -2) return -2;
	float *a = pop(stack);
	if (a != NULL) {
		float *b = pop(stack);
		if (b != NULL) {
			if (g == 4 && *b == 0)  {
				erase_after_pop(a);
				erase_after_pop(b);
				return -1;
			}
			float result = (g == 1)*(*a + *b) + (g == 2)*(*a - *b) + (g == 3)*(*a * *b) + (g == 4)*(*a / *b);
			push(stack, result);
			erase_after_pop(a);
			erase_after_pop(b);
			return 0;
		}
		erase_after_pop(a);
		return -1;
	}
	return -1;
}