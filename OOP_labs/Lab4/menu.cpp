#include "company.hpp"

namespace company {
    void menu() {
        int check = 0;
        std::string name;
        std::cout << "Enter company name: " << std::endl;
        std::getline(std::cin, name);
        std::cout << name;
        std::vector<std::pair<int, Employee *>> table;
        std::vector<Department> deps;
        Company company(name, table, deps);
        while (check != 6) {
            std::cout << "Choose what you want to do: " << std::endl;
            std::cout << "1) Show employees" << std::endl;
            std::cout << "2) Promote an employee" << std::endl;
            std::cout << "3) Demote an employee" << std::endl;
            std::cout << "4) Fire an employee" << std::endl;
            std::cout << "5) Add an employee" << std::endl;
            std::cout << "6) Exit" << std::endl;
            getnumber(check);
            while (check < 1 || check > 6) {
                std::cout << "Repeat input:" << std::endl;
                getnumber(check);
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
        }
    }
}
