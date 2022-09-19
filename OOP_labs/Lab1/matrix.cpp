#include "matrix.hpp"

using namespace matrix;

bool matrix::cmp(const std::pair<int, float> &l1, const std::pair<int, float> &l2) {
    return l1.first < l2.first;
}

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
}

void matrix::insert(Sparse_Matrix & sm, int i, int j, float elem) {
    if(i < 1 || i > sm.qty_rows || j < 1 || j > sm.qty_cols) throw "Index is uncorrect!";
    auto iter_row = sm.matrix.begin();
    for(int index = 1; index != i; index++) {
        iter_row++;
    }
    (*iter_row).push_back({j, elem});
}

void matrix::show(const Sparse_Matrix & sm) {
    std::cout << "  ";
    for(int i = 0; i < sm.qty_cols; ++i) std::cout << i + 1 << " ";
    std::cout << std::endl;
    auto iter_rows = sm.matrix.begin();
    int iter_ind = 0;
    for (int i = 0; i < sm.qty_rows; ++i) {
        std::cout << i + 1 << " ";
        auto iter_cols = (*iter_rows).begin();
        auto end_cols = (*iter_rows).end();
        for (int j = 0; j < sm.qty_cols; ++j) {
            if((*iter_cols).first != j + 1) {
                std::cout << 0 << " ";
                //if(iter_cols != end_cols) ++iter_cols;
            }
            else {
                std::cout << (*iter_cols).second << " ";
                ++iter_cols;
            }
        }
        std::cout << std::endl;
        iter_rows++;
    }
}

std::list<std::list<std::pair<int, float>>>::iterator matrix::find_iter(Sparse_Matrix & sm, bool positive) {
    std::list<std::list<std::pair<int, float>>>::iterator find_iter = sm.matrix.begin();
    int max = 0;
    int qty_el = 0;
    for(std::list<std::list<std::pair<int, float>>>::iterator iter_rows = sm.matrix.begin(); iter_rows != sm.matrix.end(); ++iter_rows) {
        for(std::list<std::pair<int, float>>::iterator iter_cols = (*iter_rows).begin(); iter_cols != (*iter_rows).end(); ++iter_cols) {
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
}

void matrix::new_matrix(Sparse_Matrix &sm) {
    (*sm.matrix.begin()).swap(*find_iter(sm, true));
    (*(--sm.matrix.end())).swap(*find_iter(sm, false));
}