#include "arc_spiral.hpp"

/*void matrix::menu() {
    int qty_rows = 0;
    int qty_cols = 0;
    int check = 1;
	while (check) {
		std::cout << "Enter quantity of rows: ";
        getnumber(qty_rows);
        std::cout << "Enter quantity of columns: ";
        getnumber(qty_cols);
        float elem = 0;
        Sparse_Matrix sm(qty_rows, qty_cols);
        int column = 0;
        auto iter = sm.matrix.begin();
        for (int row = 0; row < qty_rows; ++row) {
            for (int j = 0; j < qty_cols; ++j) {
                std::cout << "If you have finished typing in " << row + 1 << " line, enter zero" << std::endl;
                std::cout << "Enter meaningful elements in a row " << row + 1 << std::endl;
                getnumber(elem);
                if (elem == 0) break;
                std::cout << "Enter a column of this element: ";
                getnumber(column);
                try {
                    insert(sm, row + 1, column, elem);
                }
                catch (char const *message) {
                    std::cout << message << std::endl;
                    --j;
                }
            }
            (*iter).sort(matrix::cmp);
            ++iter;
        }
        matrix::show(sm);
        matrix::new_matrix(sm);
        std::cout << "New matrix: " << std::endl;
        matrix::show(sm);
        std::cout << "If you want to enter new matrix enter 1, if you want to exit enter 0" << std::endl;
        getnumber(check);
        while (true) {
            if(check != 0 && check != 1) {
                std::cout << "Repeat input:" << std::endl;
                getnumber(check);
            }
            else break;
        }
	}
}*/