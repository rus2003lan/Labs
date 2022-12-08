#include "number16.hpp"

namespace number16 {

    void dec_to_bin(int number, char *bin) {
        if (number > 0) bin[0] = '0';
        else bin[0] = '1';
        for (int i = QTY - 1; i > 0; i--) {
            if (number % 2 == 0) bin[i] = '0';
            else bin[i] = '1';
            number /= 2;
        }
    }

    void right_to_add(char *right) {
        if (right[0] == '1') {
            for (int i = QTY - 1; i > 0; i--) {
                if (right[i] == '0') {
                    right[i] = '1';
                } else {
                    right[i] = '0';
                }
            }
            char c = '1';
            for (int i = QTY - 1; i > 0; i--) {
                if (c == '0') break;
                if (right[i] == '1') right[i] = '0';
                else {
                    right[i] = '1';
                    c = '0';
                }
            }
        }
    }

    void bin_to_hex(const char *bin, char *hex) {
        const char hex_nums[17] = "0123456789ABCDEF";
        if (bin[0] == '1') hex[0] = '-';
        else hex[0] = '+';
        int hex_ind = 1;
        for (int i = 0; i < QTY - 1; i += 4) {
            int index = (bin[QTY - 1 - i] - 48) * std::pow(2, i % 4)
                        + (bin[QTY - 2 - i] - 48) * std::pow(2, (i + 1) % 4)
                        + (bin[QTY - 3 - i] - 48) * std::pow(2, (i + 2) % 4)
                        + (bin[QTY - 4 - i] - 48) * std::pow(2, (i + 3) % 4);
            hex[(QTY - 1) / 4 + 1 - hex_ind] = hex_nums[index];
            hex_ind++;
        }
    }

    int bin_to_dec(const char *nums) {
        int dec = 0;
        for (int i = QTY - 1; i > 0; i--) {
            if (nums[i] == '1') {
                dec += std::pow(2, QTY - 1 - i);
            }
        }
        if (nums[0] == '1') dec *= -1;
        return dec;
    }

    size_t size(char *nums) {
        size_t size = 0;
        for (; *nums; *nums++) {
            ++size;
        }
        return size;
    }

    void menu() {
        int check = 0;
        int number = 0;
        int number2 = 0;
        std::cout << "Enter number: ";
        getnumber(number);
        Number16 a(number);
        while (check != 11) {
            std::cout << "Choose what you want to do with the number16: " << std::endl;
            std::cout << "1) + " << std::endl;
            std::cout << "2) - " << std::endl;
            std::cout << "3) == " << std::endl;
            std::cout << "4) += " << std::endl;
            std::cout << "5) -= " << std::endl;
            std::cout << "6) < " << std::endl;
            std::cout << "7) > " << std::endl;
            std::cout << "8) Is number honest? " << std::endl;
            std::cout << "9) Print " << std::endl;
            std::cout << "10) Get number10 " << std::endl;
            std::cout << "11) Exit " << std::endl;
            getnumber(check);
            while (true) {
                if (check < 1 || check > 11) {
                    std::cout << "Repeat input:" << std::endl;
                    getnumber(check);
                } else break;
            }
            if (check == 1) {
                std::cout << "Input second operand in 10 number system " << std::endl;
                getnumber(number2);
                Number16 b(number2);
                Number16 sum = a + b;
                a.print();
                std::cout << "+" << std::endl;
                b.print();
                std::cout << "=" << std::endl;
                sum.print();
            } else if (check == 2) {
                std::cout << "Input second operand in 10 number system " << std::endl;
                getnumber(number2);
                Number16 b(number2);
                Number16 sum = a - b;
                a.print();
                std::cout << "-" << std::endl;
                b.print();
                std::cout << "=" << std::endl;
                sum.print();
            } else if (check == 3) {
                std::cout << "Input second operand in 10 number system " << std::endl;
                getnumber(number2);
                Number16 b(number2);
                std::cout << (a == b) << std::endl;
            } else if (check == 4) {
                std::cout << "Input second operand in 10 number system " << std::endl;
                getnumber(number2);
                Number16 b(number2);
                a += b;
                a.print();
            } else if (check == 5) {
                std::cout << "Input second operand in 10 number system " << std::endl;
                getnumber(number2);
                Number16 b(number2);
                a -= b;
                a.print();
            } else if (check == 6) {
                std::cout << "Input second operand in 10 number system " << std::endl;
                getnumber(number2);
                Number16 b(number2);
                std::cout << (a < b) << std::endl;
            } else if (check == 7) {
                std::cout << "Input second operand in 10 number system " << std::endl;
                getnumber(number2);
                Number16 b(number2);
                std::cout << (a > b) << std::endl;
            } else if (check == 8) {
                std::cout << a.is_honest() << std::endl;
            } else if (check == 9) {
                a.print();
            } else if (check == 10) {
                std::cout << a.get_number10() << std::endl;
            }
        }
    }
    void get_parameter(int &par) {
        getnumber(par);
        while (par < 1 || par > 2) {
            std::cout << "Uncorrect answer. Repeat input: " << std::endl;
            getnumber(par);
        }
    }
}