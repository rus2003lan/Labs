#pragma once

#include <iostream>
#include <cstring>
#include <exception>

namespace number16 {

void dec_to_bin(int number, char *bin);
int bin_to_dec(char *numbers);
char *bin_to_hex(char *numbers);
char *add_to_right(char *right);
void right_to_add(char *right);
void menu();
void get_parameter(int &parameter);

class Number16 {
    public:
        Number16();
        Number16(int number);
        Number16(char *nums);
        void print() const;
        char *get_number16() const;
        char *get_number10() const;
        Number16 &operator +=(const Number16 &term);
        Number16 operator +(const Number16 &number) const;
        Number16 operator -=(const Number16 &number);
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
    private:
        int qty;
        char * numbers;
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