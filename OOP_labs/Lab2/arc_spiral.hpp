#pragma once
#include <iostream>
#include <cmath>

namespace arc_spiral {

class Arc_spiral {
    Arc_spiral(float k) : k(k)
    {}
    float get_k() {
        return k;
    }
    void change_k(float k) {
        this->k = k;
    }
    float distance(float phi) {
        return k * phi;
    }
    float seg_square(float r1, float r2) {
        float phi = abs(r1 / k - r2 / k);
        return phi * (pow(r1, 2) + pow(r2, 2) + r1 * r2) / 6;
    }
    float coil_square(int n) {
        return M_PI * (pow(n, 2) + n * (n -1) + pow(n - 1, 2)) / 3;
    }
    float ring_square(int n) {
        return 2 * n * M_PI;
    }
    float arc_len(float phi) {
        return k / 2 * (phi * sqrt(pow(phi, 2) + 1) + std::log(phi + sqrt(pow(phi, 2) + 1)));
    }
    float curv_radius(float phi) {
        return k * pow(pow(phi, 2) + 1, 1.5) / (pow(phi, 2) + 2);
    }
    float k;
};

void menu();
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

}