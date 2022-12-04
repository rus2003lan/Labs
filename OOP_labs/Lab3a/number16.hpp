#pragma once

#define QTY 29

#include <iostream>
#include <cstring>
#include <cmath>

namespace number16 {

void bin_to_hex(const char * bin, char *hex);
void dec_to_bin(int number, char *bin);
int bin_to_dec(const char *numbers);
void right_to_add(char *right);
size_t size(char *nums);
void menu();
void get_parameter(int &parameter);

class Number16 {
    public:
        Number16(int number = 0);
        Number16(char *nums);
        Number16 &operator +=(const Number16 &term);
        Number16 operator +(const Number16 &number) const;
        Number16 &operator -=(const Number16 &number);
        Number16 operator -(const Number16 &number) const;
        Number16 operator <<(int shift);
        Number16 operator >>(int shift);
        bool operator >(const Number16 & second) const;
        bool operator <(const Number16 & second) const;
        bool operator <=(const Number16 & second) const;
        bool operator >=(const Number16 & second) const;
        bool operator ==(const Number16 & second) const;
        bool operator !=(const Number16 & second) const;
        bool is_honest() const;
        void print() const;
        int get_number10() const;
    public:
        size_t qty;
        char numbers [QTY];
};

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