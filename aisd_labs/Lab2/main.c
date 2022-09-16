#include "postfix.h"

int main() {
	while(1) {
		printf("Enter quantity elem for stack: \n");
		int qty_elem;
		int check = scanf("%d", &qty_elem);
		if (check == 1 && qty_elem > 0 && stdin_clear() == 0) {
			Stack *stack = create(qty_elem);
			int res = result(stack);
			if (res == 0) {
				float *answer = pop(stack);
				float ans = *answer;
				erase_after_pop(answer);
				float *checking = pop(stack);
				if (checking != NULL) {
					erase_after_pop(checking);
					erase(stack);
					continue;
				}
				printf("Answer: %f \n", ans);
				erase(stack);
				return 0;
			}
			else if (res == -1) {
				erase(stack);
				return 0;
			}
			else erase(stack);
		}
		else if (check == -1) return 0;
		else stdin_clear();
	}
}