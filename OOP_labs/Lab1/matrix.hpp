#include <iostream>
#include <list>

namespace matrix {

struct Sparse_Matrix {
    std::list<std::list<std::pair<int, float>>> matrix;
    int qty_rows;
    int qty_cols;
};

void menu();
void insert(Sparse_Matrix & sm, int i, int j, float elem);
void correct_column(Sparse_Matrix & sm, int j);
void show(Sparse_Matrix & sm);
template <typename T>
void getnumber(T &number) {
    char c;
    while(!(std::cin >> number) || std::cin.get(c) && c != '\n') {
        c = 0;
        std::cout << "Repeat input:" << std::endl;
        std::cin.clear();
        std::cin.ignore(10000,'\n');
    }
}
Sparse_Matrix create_matrix(int qty_rows, int qty_cols);

}
