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
            Employee & operator =(Employee const &emp);
            Employee & operator =(Employee &&emp) noexcept;
            Employee(const Employee &emp);
            Employee(Employee &&emp) noexcept;
            void swap(Employee &emp);
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
            Superuser &&to_super(Department *dep);
        private:
            std::string name;
            std::string birth_year;
            std::string education;
            std::string post;
            float salary = 0;
    };

    class Superuser : public Employee {
    private:
        Department * dep = nullptr;
    public:
        Superuser(Employee &emp, Department *dep) : Employee(emp), dep(dep){} ;
        Superuser(std::string&& name, std::string&& birth_year, std::string&& education, Department *dep,
                  std::string&& post = "Superuser", float salary = 0) : Employee(std::move(name), std::move(birth_year), std::move(education), std::move(post), salary), dep(dep) {};
        Superuser & operator =(Superuser const &super);
        Superuser & operator =(Superuser &&super) noexcept;
        ~Superuser() override = default;
        /*Superuser(const Superuser &s) : Employee(s.get_name(), s.get_birth_year(), s.get_education(), s.get_post(), s.get_salary()) {
            Department new_dep = *s.get_dep();
            dep = &new_dep;
        } ;*/
        Superuser(Superuser &&super) noexcept;
        void swap(Superuser &super);
        [[nodiscard]] Department *get_dep();
        void set_dep(Department *new_dep);
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
        virtual ~Department() = default;
        [[nodiscard]] std::string get_name() const;
        void set_name(std::string&& new_name) ;
        void set_table(std::vector<std::pair<int, Employee *>>&& new_table);
        //void add_emp(Employee & emp);
        //virtual Employee &find_emp(int id) const;
        virtual void del_emp(int id);
        void show() const;
    protected :
        [[nodiscard]] std::vector<std::pair<int, Employee *>> &get_table();
    private:
        std::string name;
        std::vector<std::pair<int, Employee *>> table;
    };

    class Company : public Department {
    private:
        std::vector<Department> deps;
        //void add_to_dep(Employee & emp, Department &dep);
    public:
        Company(std::string&& name, std::vector<std::pair<int, Employee *>>&& table, std::vector<Department>&& deps)
            : Department(std::move(name), std::move(table)), deps(deps) {};
        /*Company & operator =(Company const &company);*/
        Company & operator =(Company &&company) noexcept;
        /*Company(Company const &company) : Department(company.get_name(), company.get_table()) {
            deps = company.get_deps();
        }*/
        Department &get_dep(const std::string &name);
        Company(Company &&company) noexcept;
        ~Company() override = default;
        void swap(Company &company);
        void set_deps(std::vector<Department> &&new_deps);
        [[nodiscard]] std::vector<Department> &get_deps();
        [[nodiscard]] Employee &find_emp(int id);
        void add_emp(Employee & emp, const std::string &dep_name);
        void del_emp(int id) override;
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