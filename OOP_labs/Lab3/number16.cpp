#include "number16.hpp"

namespace number16 {

void dec_to_bin(int number, char *bin) {
    if(number > 0) bin[0] = '0';
    else bin[0] = '1';
    for (int i = 30; i > 0; i--) {
        if (number % 2 == 0) bin[i] = '0';
        else bin[i] = '1';
        number /= 2;
    }
}

void right_to_add(char *right) {
    if(right[0] ==  '1') {
        for(int i = 30; i > 0; i--) {
            if (right[i] == 0)  right[i] = 1;
            else right[i] = 0;
        }
    }
}

char *bin_to_hex(char *numbers) {
    return numbers;
}

char *add_to_right(char *right) {
    if(right[0] ==  0) return right;
    for(int i = 30; i > 0; i--) {
        if (right[i] == '0')  right[i] = '1';
        else right[i] = '0';
    }
    char c = '1';
    for(int i = 30; i > 0; i--) {
        if (c =='0') break;
        if (right[i] == '1')  right[i] = '0';
        else {
            right[i] = '1';
            c = '0';
        }
    }
    return right;
}

void menu() {
    int check = 0;
    while (check != 9) {
        std::cout << "Choose what you want to do with the archimedean spiral: " << std::endl;
        std::cout << "1)Get k" << std::endl;
        std::cout << "2)Set k" << std::endl;
        std::cout << "3)Distance" << std::endl;
        std::cout << "4)Segment square" << std::endl;
        std::cout << "5)Coil square" << std::endl;
        std::cout << "6)Ring square" << std::endl;
        std::cout << "7)Spiral length" << std::endl;
        std::cout << "8)Curve radius" << std::endl;
        std::cout << "9)Exit" << std::endl;
        getnumber(check);
        while (true) {
            if(check < 1 || check > 9) {
                std::cout << "Repeat input:" << std::endl;
                getnumber(check);
            }
            else break;
        }
        if (check == 1) {
        }
        else if (check == 2) {
        }
        else if (check == 3) {
        }
        else if (check == 4) {
        }
        else if (check == 5) {
        }
        else if (check == 6) {
        }
        else if (check == 7) {
        }
        else if (check == 8) {
        }
    }
}

void get_parameter(int &parameter) {
    getnumber(parameter);
    while (parameter <= 0 || parameter >=  31) {
        std::cout << "Uncorrect parameter (help: 0 < parameter < 31 ). Repeat input: " << std::endl;
        getnumber(parameter);
    }
}

std::string bin2hex(const std::string& input)
{
    std::string res;
    const char hex[] = "0123456789ABCDEF";
    for(auto sc : input)
    {
        unsigned char c = static_cast<unsigned char>(sc);
        res += hex[c >> 4];
        res += hex[c & 0xf];
    }
    return res;
}

Number16::Number16() {
    int n = 31;
    this->qty = n;
    char nums [n];
    this->numbers = nums;
}
Number16::Number16(int number) {
    int n = 31;
    this->qty = n;
    char nums [n];
    dec_to_bin(number, nums);
    this->numbers = nums;
}
Number16::Number16(char *nums) {
    int n = 31;
    this->qty = n;
    this->numbers = nums;
}
void Number16::print() const{
    std::cout << bin_to_hex(numbers) << std::endl;
}

char *Number16::get_number() const {
    return bin_to_hex(numbers);
}

Number16 &Number16::operator +=(const Number16 &term) {
    char copy [31];
    strcpy(copy, term.numbers);
    right_to_add(copy);
    right_to_add(numbers);
    char c = '0';
    for(int i = 30; i >= 0; i--) {
        numbers[i] = (numbers[i] + copy[i] + c) % 2;
        if (numbers[i] == '1' && copy[i] == '1' || numbers[i] == '1' && c == '1' || copy[i] == '1' && c == '1') c = '1';
        else c = '0';
    }
    add_to_right(numbers);
    return *this;
}
Number16 Number16::operator +(const Number16 &number) const{
    Number16 sum = *this;
    sum += number;
    return sum;
}
Number16 Number16::operator -=(const Number16 &number) {
    if (number.numbers[0] == 0) number.numbers[0] = 1;
    else number.numbers[0] == 0;
    *this += number;
    return *this;
}
Number16 Number16::operator -(const Number16 &number) const{
    Number16 dif = *this;
    dif -= number;
    return dif;
}
Number16 Number16::operator <<(int shift) {
    if (shift > qty || shift < qty) throw "Uncorrect shift";
    char new_numbers [qty];
    new_numbers[0] = numbers[0];
    for(int i = 1; i < qty - shift; i++) {
        new_numbers[i] = numbers[i + shift];
    }
    for (int i = 1; i <= shift; i++) {
        new_numbers[qty - i] = '0';
    }
    numbers = new_numbers;
    return *this;
}

Number16 Number16::operator >>(int shift) {
    if (shift > qty || shift < qty) throw "Uncorrect shift";
    char new_numbers [qty];
    new_numbers[0] = numbers[0];
    for(int i = 1; i < qty - shift; i++) {
        new_numbers[i + shift] = numbers[i];
    }
    for (int i = 1; i <= shift; i++) {
        new_numbers[i] = '0';
    }
    numbers = new_numbers;
    return *this;
}

bool Number16::operator >(const Number16 & second) const{
    if(numbers[0] > second.numbers[0]) return false;
    else if (numbers[0] < second.numbers[0]) return true;
    for (int i = 1; i < qty; i++) {
        if(numbers[i] > second.numbers[i]) return true;
        else if (numbers[i] < second.numbers[i]) return false;
        else continue;
    }
    return false;
}

bool Number16::operator <(const Number16 & second) const{
    if (*this > second || numbers[0] < second.numbers[0]) return false;
    else {
        for (int i = 1; i < qty; i++) {
            if(numbers[i] < second.numbers[i]) return true;
        }
        return false;
    }
}

bool Number16::operator ==(const Number16 & second) const{
    return !(*this > second) && !(*this < second);
}

bool Number16::operator <=(const Number16 & second) const {
    return !(*this > second);
}

bool Number16::operator >=(const Number16 & second) const {
    return !(*this < second);
}

bool Number16::is_honest() const {
    return this->numbers[qty - 1] == '0';
}

bool Number16::operator !=(const Number16 & second) const{
    return !(*this == second);
}

int Number16::get_number10() const {
    return bin_to_dec(numbers);
}

}