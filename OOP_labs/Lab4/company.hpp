#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <typeinfo>
#include <exception>

namespace company {

    void menu();
    void get_parameter(int &parameter);

    class Employee {
        public:
            Employee(std::string name, std::string birth_year, std::string education,
                     std::string post = "Employee", float salary = 0) : name(name), birth_year(birth_year),
                     education(education), post(post), salary(salary) {};
            Employee & operator =(const Employee &emp);
            Employee(const Employee &emp);
            std::string info() const;
            std::string get_post() const;
            void set_post(std::string post);
            float get_salary() const;
            void set_salary(const float salary);
            void to_super();
        private:
            std::string name;
            std::string birth_year;
            std::string education;
            std::string post;
            float salary;
    };

    class Department {
    public:
        Department(std::string name, std::vector<std::pair<int, Employee *>> table) : name(name), table(table) {};
        Department & operator =(const Department &dep);
        Department(const Department &dep);
        void info() const;
        void add_emp(Employee & emp);
        Employee &find_emp(int id) const;
        void del_emp(int id);
        void show() const;
    private:
        std::string name;
        std::vector<std::pair<int, Employee *>> table;
    };

    class Company : public Department {
    private:
        std::vector<Department> deps;
    public:
        Company(std::string name, std::vector<std::pair<int, Employee *>> table, std::vector<Department> deps) : Department(name, table), deps(deps) {};
        Company & operator =(const Company &company);
        Company(const Company &company);
        Department &get_dep(std::string name);
        size_t count_deps() const;
    };

    class Superuser : public Employee {
    private:
        Department * dep;
    public:
        Superuser(std::string name, std::string birth_year, std::string education, Department *dep,
                  std::string post = "Superuser", float salary = 0) : Employee(name, birth_year, education, post, salary), dep(dep) {};
        /*Company & operator =(const Company &company);
        Company(const Company &company);
        Department &get_dep(std::string name);*/
        size_t count_deps();
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