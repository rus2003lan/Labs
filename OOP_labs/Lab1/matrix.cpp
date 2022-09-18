#include "matrix.hpp"

using namespace matrix;

void menu() {
    int qty_rows = 0;
    int qty_cols = 0;
	while (true) {
		std::cout << "Enter quantity of rows: ";
        getnumber(qty_rows);
        std::cout << "Enter quantity of columns: ";
        getnumber(qty_cols);
        float elem = 0;
        Sparse_Matrix sm = create_matrix(qty_rows, qty_cols);
        int j = 0;
        int column;
        for (int i = 0; i < qty_rows; ++i) {
            for (int j = 0; j < qty_cols; ++j) {
                std::cout << "If you have finished typing in " << i + 1 << " line, enter zero" << std::endl;
                std::cout << "Enter meaningful elements in a row " << i + 1 << std::endl;
                getnumber(elem);
                if (elem == 0) break;
                std::cout << "Enter a column of this element: ";
                getnumber(column);
                insert(sm, i, column, elem);
            }
        }
        matrix::show(sm);

	}
}

void matrix::insert(Sparse_Matrix & sm, int i, int j, float elem) {
    auto iter_row = sm.matrix.begin();
    for(int index = 1; index != i; index++) {
        iter_row++;
    }
    (*iter_row).push_back({j, elem});
}

Sparse_Matrix matrix::create_matrix(int qty_rows, int qty_cols) {
    Sparse_Matrix sm;
    sm.qty_cols = qty_cols;
    sm.qty_rows = qty_rows;
    std::list<std::list<std::pair<int, float>>> matrix;
    sm.matrix = matrix;
    auto iter = sm.matrix.begin();
    for (int i = 0; i < qty_rows; i++) { //здесь можно юзать push_back?
        std::list<std::pair<int, float>> row;
        *iter = row;
        iter++;
    }
    return sm;
}

void show(Sparse_Matrix & sm) {
    std::cout << "  ";
    for(int i = 0; i < sm.qty_cols; ++i) std::cout << i + 1 << " ";
    std::cout << std::endl;
    auto iter_rows = sm.matrix.begin();
    for (int i = 0; i < sm.qty_rows; ++i) {
        std::cout << i + 1 << " ";
        for (auto iter_cols = (*iter_rows).begin(); iter_cols != (*iter_rows).end(); ++iter_cols) {
            std::cout << (*iter_cols).second << " ";
        }
        std::cout << std::endl;
        iter_rows++;
    }
}