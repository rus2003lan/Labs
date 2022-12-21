#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <typeinfo>
#include <exception>

namespace company {

    void menu();

    static int count = 0;

    class Employee {
        public:
            Employee() = default;
            Employee(std::string&& name, std::string&& birth_year, std::string&& education, std::string&& post = "Employee", float salary = 0)
                : name(name), birth_year(birth_year), education(education), post(post), salary(salary) {};
            Employee & operator =(Employee const &emp);
            Employee & operator =(Employee &&emp) noexcept;
            Employee(const Employee &emp);
            Employee(Employee &&emp) noexcept;
            ~Employee() = default;
            [[nodiscard]] std::string info() const;
            [[nodiscard]] std::string get_post() const;
            void set_post(std::string&& new_post);
            [[nodiscard]] float get_salary() const;
            void set_salary(float const &new_salary);
            void to_super();
            void swap(Employee &emp);
        protected:
            std::string name;
            std::string birth_year;
            std::string education;
            std::string post;
            float salary;
    };

    class Department {
    public:
        Department() = default;
        Department(std::string&& name, std::vector<std::pair<int, Employee *>>&& table) : name(name), table(table) {};
        Department & operator =(Department const &dep);
        Department & operator =(Department &&dep) noexcept;
        Department(Department const &dep);
        Department(Department &&dep) noexcept;
        void swap(Department &dep);
        [[nodiscard]] std::string info() const;
        void del_emp(int id);
        void show() const;
    protected:
        std::string name;
        std::vector<std::pair<int, Employee *>> table;
    };

    class Company : public Department {
    private:
        std::vector<Department> deps;
    public:
        Company(std::string&& name, std::vector<std::pair<int, Employee *>>&& table, std::vector<Department>&& deps)
            : Department(std::move(name), std::move(table)), deps(deps) {};
        Company & operator =(Company const &company);
        Company(Company const &company);
        Department &get_dep(std::string name);
        Company(Company &&company) noexcept;
        Company & operator =(Company &&company) noexcept;
        void swap(Company &company);
        [[nodiscard]] Employee &&find_emp(int id) const;
        void add_emp(Employee & emp, std::string&& dep);
        void del_emp(int id);
    };

    class Superuser : public Employee {
    private:
        Department * dep;
    public:
        Superuser(std::string&& name, std::string&& birth_year, std::string&& education, Department *dep,
                  std::string&& post = "Superuser", float salary = 0) : Employee(std::move(name), std::move(birth_year), std::move(education), std::move(post), salary), dep(dep) {};
        Superuser & operator =(Superuser const &super);
        Superuser & operator =(Superuser &&super) noexcept;
        Superuser(Superuser const &super);
        Superuser(Superuser &&super) noexcept;
        void swap(Superuser &super);
        Department &get_dep(std::string name);
    };

    template <typename T>
    void get_number(T &number) {
        char c;
        while(!(std::cin >> number) || std::cin.get(c) && c != '\n') {
            c = 0;
            std::cout << "Repeat input:" << std::endl;
            std::cin.clear();
            std::cin.ignore(10000,'\n');
        }
    }

}