#include <iostream>
#include <list>

namespace matrix {

struct Sparse_Matrix {
    std::list<std::list<std::pair<int, float>>> matrix;
    int qty_rows;
    int qty_cols;
};

void menu();
template <typename T>
void getnumber(T & number);
void insert(Sparse_Matrix & sm, int i, int j, float elem);
void correct_column(Sparse_Matrix & sm, int j);
}
