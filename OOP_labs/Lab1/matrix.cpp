/*#include "matrix.hpp"

using namespace matrix;

void matrix::menu() {
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
        for (int row = 0; row < qty_rows; ++row) {
            for (int j = 0; j < qty_cols; ++j) {
                std::cout << "If you have finished typing in " << row + 1 << " line, enter zero" << std::endl;
                std::cout << "Enter meaningful elements in a row " << row + 1 << std::endl;
                getnumber(elem);
                if (elem == 0) break;
                std::cout << "Enter a column of this element: ";
                getnumber(column);
                insert(sm, row, column, elem);
            }
        }
        matrix::show(sm);
        matrix::new_matrix(sm);
        matrix::show(sm);
        std::cout << "If you want to enter new matrix enter 1, if you want to exit enter 0" << std::endl;
        getnumber(check);
        while (check != 0 || check != 1) {
            std::cout << "Repeat input:" << std::endl;
            getnumber(check);
        }
	}
}

void matrix::insert(Sparse_Matrix & sm, int i, int j, float elem) {
    auto iter_row = sm.matrix.begin();
    for(int index = 1; index != i; index++) {
        iter_row++;
    }
    (*iter_row).push_back({j, elem});
}

void matrix::show(Sparse_Matrix & sm) {
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

void matrix::new_matrix(Sparse_Matrix &sm) {
    (*sm.matrix.begin()).swap(*find_iter(sm, true));
    (*(--sm.matrix.end())).swap(*find_iter(sm, false));
}

auto matrix::find_iter(Sparse_Matrix & sm, bool positive) {
    auto find_iter = sm.matrix.begin();
    int max = 0;
    int qty_el = 0;
    for(auto iter_rows = sm.matrix.begin(); iter_rows != sm.matrix.end(); ++iter_rows) {
        for(auto iter_cols = (*iter_rows).begin(); iter_cols != (*iter_rows).end(); ++iter_cols) {
            if (positive) {
                if((*iter_cols).second > 0) ++qty_el;
            }
            else {
                if((*iter_cols).second < 0) ++qty_el;
            }
        }
        if(max < qty_el) {
            max = qty_el;
            find_iter = iter_rows;
        }
        qty_el = 0;
    }
    return find_iter;
}*/