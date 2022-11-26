#include "number16.hpp"

namespace number16 {

void dec_to_bin(int number, char *bin) {
    if (number > 0) bin[0] = '0';
    else bin[0] = '1';
    for (int i = 29; i > 0; i--) {
        if (number % 2 == 0) bin[i] = '0';
        else bin[i] = '1';
        number /= 2;
    }
}

void right_to_add(char *right) {
    if (right[0] == '1') {
        for (int i = 29; i > 0; i--) {
            if (right[i] == '0') {
                right[i] = '1';
            } else {
                right[i] = '0';
            }
        }
        char c = '1';
        for (int i = 29; i > 0; i--) {
            if (c == '0') break;
            if (right[i] == '1') right[i] = '0';
            else {
                right[i] = '1';
                c = '0';
            }
        }
    }
}

void get_parameter(int &parameter) {
    getnumber(parameter);
    while (parameter <= 0 || parameter >= 31) {
        std::cout << "Uncorrect parameter (help: 0 < parameter < 31 ). Repeat input: " << std::endl;
        getnumber(parameter);
    }
}
}

/*void bin_to_hex(char * bin)
{
    while(binaryNum!=0)
    {
        rem = binaryNum%10;
        hex = hex + (rem*mul);
        if(chk%4==0)
        {
            if(hex<10)
                hexDecNum[i] = hex+48;
            else
                hexDecNum[i] = hex+55;
            mul = 1;
            hex = 0;
            chk = 1;
            i++;
        }
        else
        {
            mul = mul*2;
            chk++;
        }
        binaryNum = binaryNum/10;
    }
    if(chk!=1)
        hexDecNum[i] = hex+48;
    if(chk==1)
        i--;
}*/