#include "matrix.hpp"

/*int main() { 
    Sparse_Matrix sm;
    std::list<std::pair<int, int>> row1;
    std::list<std::pair<int, int>> row2;
    for (int i = 0; i < 3; ++i) {
        row1.push_back({i, i});
        row2.push_back({i + 7, i + 7});
    }
    sm.matrix.push_back(row1);
    sm.matrix.push_back(row2);
    auto iter1 = sm.matrix.begin();
    auto iter2 = iter1++;
    (*iter1).swap(*iter2);
    return 0;
}*/

int main() {
    int a;
    float b;
    matrix::getnumber(a);
    matrix::getnumber(b);
    std::cout << a;
    std::cout << " " << b;
    return 0;
}