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
size_t size(const char *nums);
void menu();
void get_parameter(int &parameter);

class Number16 {
    friend Number16 operator -(const Number16 &number1, const Number16 &number2);
    friend Number16 operator +(const Number16 &number1, const Number16 &number2);
    friend bool operator >(const Number16 & first, const Number16 & second);
    friend bool operator <(const Number16 & first, const Number16 & second);
    friend bool operator <=(const Number16 & first, const Number16 & second);
    friend bool operator >=(const Number16 & first, const Number16 & second);
    friend bool operator ==(const Number16 & first, const Number16 & second);
    friend bool operator !=(const Number16 & first, const Number16 & second);
    public:
        Number16(const int number = 0);
        Number16(const char *nums);
        Number16 &operator +=(const Number16 &term);
        Number16 &operator -=(const Number16 &number);
        Number16 operator <<(int shift);
        Number16 operator >>(int shift);
        bool is_honest() const;
        void print() const;
        int get_number10() const;
    private:
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