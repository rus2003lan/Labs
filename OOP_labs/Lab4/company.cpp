#include "company.hpp"

namespace company {

    Employee & Employee::operator =(Employee const &emp) {
        if (this != &emp) {
            Employee(emp).swap(*this);
        }
        return *this;
    }

    Employee & Employee::operator =(Employee &&emp) noexcept{
        swap(emp);
        return *this;
    }

    Employee::Employee(Employee &&emp) noexcept{
        swap(emp);
    }

    void Employee::swap(Employee &emp) {
        std::swap(name, emp.name);
        std::swap(birth_year, emp.birth_year);
        std::swap(education, emp.education);
        std::swap(post, emp.post);
        std::swap(salary, emp.salary);
    }

    Employee::Employee(const Employee &emp) {
        name = emp.name;
        birth_year = emp.birth_year;
        education = emp.education;
        post = emp.post;
        salary = emp.salary;
    }

    void Employee::to_super() {
        // some logics
    }

    std::string Employee::info() const{
        return name;
    }

    std::string Employee::get_post() const{
        return post;
    }

    void Employee::set_post(std::string&& new_post) {
        if(new_post != "Employee" || new_post != "Superuser") {
            throw std::invalid_argument("Incorrect post");
        }
        post = new_post;
    }

    float Employee::get_salary() const{
        return salary;
    }

    void Employee::set_salary(float const &new_salary) {
        if (new_salary < 0) {
            throw std::invalid_argument("Salary < 0");
        }
        salary = new_salary;
    }

    Department & Department::operator =(Department const &dep) {
        Department(dep).swap(*this);
        return *this;
    }

    Department & Department::operator =(Department &&dep) noexcept{
        swap(dep);
        return *this;
    }

    Department::Department(Department const &dep) {
        name = dep.name;
        table = dep.table;
    }

    Department::Department(Department &&dep) noexcept{
        swap(dep);
    }

    std::string Department::info() const {
        return name;
    }

    void Company::add_emp(Employee & emp, std::string&& dep) {
        std::pair<int, Employee *> pair = {count, &emp};
        table.push_back(pair);
        std::sort(table.begin(), table.end());
        ++count;
        // надо как-то добавить в компанию инфу
    }

    Employee && Company::find_emp(int id) const {
        if (id < 0 || id > count) throw std::invalid_argument("Incorrect id");
        for(auto it = table.begin(); it != table.end(); it++) {
            if ((*it).first == id) {
                return std::move(*((*it).second));
            }
        }
    }

    void Company::del_emp(int id) {
        if (id < 0 || id > count) throw std::invalid_argument("Incorrect id");
        auto it = table.begin();
        for(it; it != table.end(); it++) {
            if ((*it).first == id) {
               break;
            }
        }
        for(auto it2 = it + 1; it2 != table.end(); it2++) {
            --(*it2).first;
        }
        table.erase(it);
        --count;
    }

    void Department::show() const {
        std::cout << "ID    NAME  " << std::endl << std::endl;
        for(auto iter = table.begin(); iter != table.end(); iter++) {
            std::cout << (*iter).first << "    " << (*iter).second->info() << std::endl;
        }
    }

    void Department::swap(Department &dep) {
        std::swap(name, dep.name);
        std::swap(table, dep.table);
    }

    Company & Company::operator =(Company const &company) {
        if (this != &company) {
            Company(company).swap(*this);
        }
        return *this;
    }

    Company::Company(Company const &company) {
        name = company.name;
        table = company.table;
        deps = company.deps;
    }

    Department &Company::get_dep(std::string name) {
        for(auto it = deps.begin(); it != deps.end(); ++it) {
            if ((*it).info() == name) {
                return *it;
            }
        }
    }

    Company::Company(Company &&company) noexcept {
        swap(company);
    }

    Company & Company::operator =(Company &&company) noexcept {
        swap(company);
        return *this;
    }

    void Company::swap(Company &company) {
        std::swap(name, company.name);
        std::swap(table, company.table);
        std::swap(deps, company.deps);
    }

    Superuser & Superuser::operator =(Superuser const &superuser) {
        if (this != &superuser) {
            dep = superuser.dep;
            name = superuser.name;
            birth_year = superuser.birth_year;
            education = superuser.education;
            post = superuser.post;
            salary = superuser.salary;
        }
        return *this;
    }

    Superuser::Superuser(Superuser const &superuser) {
        dep = superuser.dep;
        name = superuser.name;
        birth_year = superuser.birth_year;
        education = superuser.education;
        post = superuser.post;
        salary = superuser.salary;
    }
    Department &get_dep(std::string name) {

    }

    Superuser::Superuser(Superuser &&superuser) noexcept {
        swap(superuser);
    }

    Superuser & Superuser::operator =(Superuser &&superuser) noexcept {
        swap(superuser);
        return *this;
    }

    void Superuser::swap(Superuser &superuser) {
        std::swap(name, superuser.name);
        std::swap(birth_year, superuser.birth_year);
        std::swap(education, superuser.education);
        std::swap(post, superuser.post);
        std::swap(salary, superuser.salary);
        std::swap(dep, superuser.dep);
    }
}