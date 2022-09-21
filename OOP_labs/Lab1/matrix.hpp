#pragma once
#include <iostream>
#include <list>

namespace matrix {

struct Sparse_Matrix {
    Sparse_Matrix(int qty_rows, int qty_cols) {
        this->qty_cols = qty_cols;
        this->qty_rows = qty_rows;
        std::list<std::list<std::pair<int, float>>> matrix;
        for (int i = 0; i < qty_rows; i++) {
            std::list<std::pair<int, float>> row;
            matrix.push_back(row);
        }
        this->matrix = matrix;
    }
    std::list<std::list<std::pair<int, float>>> matrix;
    int qty_rows;
    int qty_cols;
};

void menu();
void insert(Sparse_Matrix & sm, int i, int j, float elem);
void correct_column(Sparse_Matrix & sm, int j);
void show(const Sparse_Matrix & sm);
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
void new_matrix(Sparse_Matrix &sm);
std::list<std::list<std::pair<int, float>>>::iterator find_iter(Sparse_Matrix & sm, bool positive);
bool cmp(const std::pair<int, float> &l1, const std::pair<int, float> &l2);
}
