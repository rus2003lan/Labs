#include "matrix.hpp"

namespace matrix {
void menu() {
    int qty_rows = 0;
    int qty_cols = 0;
	while (true) {
		std::cout << "Enter quantity of rows: ";
        getnumber(qty_rows);
        std::cout << "Enter quantity of columns: ";
        getnumber(qty_cols);
        float elem;
        Sparse_Matrix sm;
        sm.qty_cols = qty_cols;
        sm.qty_rows = qty_rows;
        std::list<std::list<std::pair<int, float>>> matrix;
        sm.matrix = matrix;
        int j = 0;
        for (int i = 0; i < qty_rows; ++i) {
            std::cout << "Enter meaningful elements in a row " << i + 1<< std::endl;
            getnumber(elem);
            std::cout << "Enter a column of this element: ";
            getnumber(j);
            try {
                correct_column(sm, j);
            }
            catch (...) {
                std::cout << "Incorrect number of column, please, repeat input of column's number:" << std::endl;
            }
            insert(sm, i, j, elem);
        }

	}
}

void insert(Sparse_Matrix & sm, int i, int j, float elem) {
    auto iter = sm.matrix.begin();
    
}

/*int getint(int *number) {
	int check1 = scanf("%d", number);
	int check2 = stdin_clear();
	if (check1 == -1) return -1;
	else if (check1 == 0 || check2 == 1) return 1;
	else return 0;
}

int stdin_clear() {
	char tmp;
	int i = 0;
	while (scanf("%1[^\n]", &tmp) == 1) i++;
	if(i != 0) return 1;
	scanf("%*c");
	return 0;
}

char *get_str() {
    char buf[81] = {0};  // BUFSIZ - константа для длины буфера
    char *res = NULL;
    unsigned int len = 0;
    unsigned int n = 0;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        } else if (n > 0) {
            unsigned int chunk_len = strlen(buf);
            unsigned int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
    }

    return res;
}
*/
}