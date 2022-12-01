#include "number16.hpp"

int main () {
    int check = 0;
    while(true) {
        number16::menu();
        std::cout << "You want to create new number16?" << std::endl << "1)YES 2)NO" << std::endl;
        number16::get_parameter(check);
        if (check == 2) break;
    }

    return 0;
}