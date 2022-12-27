#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <typeinfo>
#include <exception>

namespace company {
    void menu();
    class Department;
    class Superuser;
    class Employee;
    class Company;

    static int count = 0;

    class Employee {
        public:
            Employee() = default;
            Employee(std::string&& name, std::string&& birth_year, std::string&& education, std::string&& post, float salary)
                : name(name), birth_year(birth_year), education(education), post(post), salary(salary) {};
            Employee(const Employee &emp) = default;
            Employee(Employee &&emp) noexcept;
            Employee & operator =(Employee const &emp);
            Employee & operator =(Employee &&emp) noexcept;
            virtual ~Employee() = default;

            [[nodiscard]] std::string get_name() const;
            void set_name(std::string&& new_name);
            [[nodiscard]] std::string get_birth_year() const;
            void set_birth_year(std::string&& new_birth_year);
            [[nodiscard]] std::string get_education() const;
            void set_education(std::string&& new_education);
            [[nodiscard]] std::string get_post() const;
            void set_post(std::string&& new_post);
            [[nodiscard]] float get_salary() const;
            void set_salary(float const &new_salary);
        private:
            std::string name;
            std::string birth_year;
            std::string education;
            std::string post;
            float salary = 0;
            void swap(Employee &emp);
    };

    class Superuser : public Employee {
    private:
        Department * dep = nullptr;
        void swap(Superuser &super); // ??
    public:
        Superuser(Employee &&emp, Department *dep) : Employee(emp), dep(dep) {} ;
        Superuser(std::string&& name, std::string&& birth_year, std::string&& education, Department *dep,
                  std::string&& post = "Superuser", float salary = 0) : Employee(std::move(name), std::move(birth_year), std::move(education), std::move(post), salary), dep(dep) {};
        Superuser(Superuser &&super) noexcept;
        Superuser(const Superuser &s) = default; // ???
        Superuser & operator =(Superuser const &super);
        Superuser & operator =(Superuser &&super) noexcept;
        ~Superuser() override = default;

        [[nodiscard]] Department *get_dep();
        void set_dep(Department *new_dep);
    };

    class Department {
    public:
        Department(std::string&& name, std::vector<std::pair<int, Employee *>>&& table) : name(name), table(table) {};
        Department(Department const &dep) = default;
        Department(Department &&dep) noexcept;
        Department & operator =(Department const &dep);
        Department & operator =(Department &&dep) noexcept;
        ~Department() = default;

        void add_emp(int id, Employee &emp);
        Employee &get_emp(int id);
        void del_emp(int id);
        void show() const;
        void to_super(int id);
        [[nodiscard]] std::string get_name() const;
        void set_name(std::string&& new_name);
        [[nodiscard]] std::vector<std::pair<int, Employee *>> &get_table();
        void set_table(std::vector<std::pair<int, Employee *>>&& new_table);
        std::vector<std::pair<int, Employee *>>::iterator get_emp_it(int id);
    private:
        std::string name;
        std::vector<std::pair<int, Employee *>> table;
        void swap(Department &dep);
    };

    class Company {
    private:
        std::vector<Department> deps;
        std::string name;
        void swap(Company &company);
    public:
        Company(std::string&& name, std::vector<Department>&& deps): name(name),  deps(deps) {};
        Company(Company &&company) noexcept;
        Company(Company const &company) = default;
        Company & operator =(Company const &company);
        Company & operator =(Company &&company) noexcept;
        ~Company() = default;

        [[nodiscard]] std::vector<Department> &get_deps();
        void set_deps(std::vector<Department> &&new_deps);
        [[nodiscard]] std::string &get_name();
        void set_name(std::string &&new_name);
        Department &get_dep(const std::string &name);
        Department &get_dep(int id);
        Employee &get_emp(int id);
        void add_emp(Employee &emp, const std::string &dep_name);
        void del_emp(int id);
        void to_super(int id);
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

    Employee &get_emp();

}