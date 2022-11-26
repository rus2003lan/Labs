#include "number16.hpp"

int main () {
    /*while(1) {
        int n = 0;
        std::cin >> std::hex >> n;
        std::cout << n << "\n";
    }*/
    //number16::menu();
    number16::Number16 c = -38;
    std::cout << c.numbers << std::endl;
    number16::Number16 d = -212;
    std::cout << d.numbers << std::endl;
    number16::Number16 c_d = c + d;
    std::cout << c_d.numbers << std::endl;
    /*const std::string s(a);
    std::string asd = number16::bin2hex(s);
    std::cout << asd << std::endl;*/
    return 0;
}