#include "number16.hpp"

namespace number16 {

Number16::Number16(int number) {
    qty = QTY;
    numbers = new char [QTY];
    dec_to_bin(number, numbers);
}
Number16::Number16(char *nums) {
    qty = QTY;
    numbers = new char [QTY];
    strcpy(numbers, nums);
}

Number16::~Number16() {
    delete [] numbers;
}

Number16::Number16(Number16 const & number) {
    numbers = new char [number.qty];
    qty = number.qty;
    strcpy(numbers, number.numbers);
}

void Number16::print() const{
    char hex[(QTY - 1) / 4 + 1];
    bin_to_hex(numbers, hex);
    std::cout << hex << std::endl;
}

Number16 & Number16::operator =(Number16 const & number) {
    if (this != &number) {
        delete [] numbers;
        qty = number.qty;
        numbers = new char [qty];
        strcpy(numbers, number.numbers);
    }
    return *this;
}

Number16 &Number16::operator +=(const Number16 &term) {
    char copy [QTY];
    strcpy(copy, term.numbers);
    right_to_add(copy);
    right_to_add(numbers);
    char * a = copy;
    char * b = numbers;
    char c = '0';
    char pred = '0';
    for(int i = QTY - 1; i >= 0; i--) {
        pred = numbers[i];
        numbers[i] = (numbers[i] + copy[i] + c) % 2 + 48;
        if (pred == '1' && copy[i] == '1' || pred == '1' && c == '1' || copy[i] == '1' && c == '1') c = '1';
        else c = '0';
    }
    right_to_add(numbers);
    return *this;
}
Number16 Number16::operator +(const Number16 &number) const{
    Number16 sum = *this;
    sum += number;
    return sum;
}
Number16 &Number16::operator -=(const Number16 &number) {
    char copy [QTY];
    strcpy(copy, number.numbers);
    if (copy[0] == '0') copy[0] = '1';
    else copy[0] = '0';
    Number16 neg_number(copy);
    *this += neg_number;
    return *this;
}
Number16 Number16::operator -(const Number16 &number) const{
    Number16 dif = *this;
    dif -= number;
    return dif;
}
Number16 Number16::operator <<(int shift) {
    char new_numbers [qty];
    new_numbers[0] = numbers[0];
    for(int i = 1; i < qty - shift; i++) {
        new_numbers[i] = numbers[i + shift];
    }
    for (int i = 0; i <= shift + 1; i++) {
        new_numbers[qty - i - 1] = '0';
    }
    strcpy(numbers, new_numbers);
    return *this;
}

Number16 Number16::operator >>(int shift) {
    char new_numbers [qty];
    new_numbers[0] = numbers[0];
    for(int i = 1; i < qty - shift - 1; i++) {
        new_numbers[i + shift] = numbers[i];
    }
    for (int i = 1; i <= shift; i++) {
        new_numbers[i] = '0';
    }
    strcpy(numbers, new_numbers);
    return *this;
}

bool Number16::operator >(const Number16 & second) const{
    bool flag = true;
    if(numbers[0] > second.numbers[0]) return false;
    else if (numbers[0] < second.numbers[0]) return true;
    else if (numbers[0] == '1' && second.numbers[0] == '1') flag = false;
    for (int i = 1; i < qty; i++) {
        if(numbers[i] > second.numbers[i]) return flag;
        else if (numbers[i] < second.numbers[i]) return !flag;
        else continue;
    }
    return false;
}

bool Number16::operator <(const Number16 & second) const{
    bool flag = true;
    if (*this > second || numbers[0] < second.numbers[0]) return false;
    else if (numbers[0] > second.numbers[0]) return true;
    else if (numbers[0]  == '1' && second.numbers[0] == '1') flag = false;
    for (int i = 1; i < qty; i++) {
        if(numbers[i] < second.numbers[i]) return flag;
        else if (numbers[i] > second.numbers[i]) return !flag;
    }
    return false;
}

bool Number16::operator ==(const Number16 & second) const{
    return !(*this > second) && !(*this < second);
}

bool Number16::operator <=(const Number16 & second) const {
    bool e = !(*this > second);
    return e;
}

bool Number16::operator >=(const Number16 & second) const {
    return !(*this < second);
}

bool Number16::is_honest() const {
    return numbers[qty - 1] == '0';
}

bool Number16::operator !=(const Number16 & second) const{
    return !(*this == second);
}

int Number16::get_number10() const {
    return number16::bin_to_dec(numbers);;
}

}