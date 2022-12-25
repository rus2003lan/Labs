#include "company.hpp"

namespace company {

    Employee & Employee::operator =(Employee const &emp) {
        if (this == &emp) return *this;
        Employee(emp).swap(*this);
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

    Superuser &&Employee::to_super(Department *dep) {
        Superuser super(*this, dep);
        return std::move(super);
    }

    std::string Employee::get_name() const{
        return name;
    }

    void Employee::set_name(std::string&& new_name) {
        name = new_name;
    }

    std::string Employee::get_birth_year() const {
        return birth_year;
    }

    void Employee::set_birth_year(std::string&& new_birth_year) {
        birth_year = new_birth_year;
    }

    std::string Employee::get_post() const{
        return post;
    }

    void Employee::set_post(std::string&& new_post) {
        post = new_post;
    }

    std::string Employee::get_education() const {
        return education;
    }

    void Employee::set_education(std::string&& new_education) {
        education = new_education;
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
        if (this == &dep) return *this;
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

    std::string Department::get_name() const {
        return name;
    }

    void Department::set_name(std::string&& new_name)  {
        name= new_name;
    }

    void Department::show() const {
        std::cout << "ID    NAME  " << std::endl << std::endl;
        for(auto iter = table.begin(); iter != table.end(); iter++) {
            std::cout << (*iter).first << "    " << (*iter).second->get_name() << std::endl;
        }
    }

    std::vector<std::pair<int, Employee *>> &Department::get_table() {
        return table;
    }

    void Department::set_table(std::vector<std::pair<int, Employee *>>&& new_table) {
        table = new_table;
    }

    void Department::swap(Department &dep) {
        std::swap(name, dep.name);
        std::swap(table, dep.table);
    }

    /*void Department::add_emp(Employee & emp) {
        std::pair<int, Employee *> pair = {count, &emp};
        table.push_back(pair);
        std::sort(table.begin(), table.end());
    }*/




    Employee & Company::find_emp(int id) {
        if (id < 0 || id > count) throw std::invalid_argument("Incorrect id");
        std::vector<std::pair<int, Employee *>> my_table = get_table();
        for(auto it = my_table.begin(); it != my_table.end(); it++) {
            if ((*it).first == id) {
                return *(*it).second;
            }
        }
    }

    void Company::del_emp(int id) {
        if (id < 0 || id > count) throw std::invalid_argument("Incorrect id");
        std::vector<std::pair<int, Employee *>> my_table = get_table();
        auto it = my_table.begin();
        for(it; it != my_table.end(); it++) {
            if ((*it).first == id) {
               break;
            }
        }
        for(auto it2 = it + 1; it2 != my_table.end(); it2++) {
            --(*it2).first;
        }
        my_table.erase(it);
        --count;
    }

    /*Company & Company::operator =(Company const &company) {
        if (this == &company) return *this;
        Company(company).swap(*this);
        return *this;
    }*/

    Department &Company::get_dep(const std::string &dep_name) {
        for(auto it = deps.begin(); it != deps.end(); ++it) {
            if ((*it).get_name() == dep_name) {
                return *it;
            }
        }
        throw std::invalid_argument("No such department");
    }

    void Company::set_deps(std::vector<Department> &&new_deps) {
        deps = new_deps;
    }
    std::vector<Department> &Company::get_deps() {
        return deps;
    }

    Company::Company(Company &&company) noexcept {
        swap(company);
    }

    Company & Company::operator =(Company &&company) noexcept {
        swap(company);
        return *this;
    }

    void Company::swap(Company &company) {
        std::string tmp = get_name();
        set_name(company.get_name());
        company.set_name(std::move(tmp));
        std::vector<std::pair<int, Employee *>> tmp0 = get_table();
        set_table(std::move(company.get_table()));
        company.set_table(std::move(tmp0));
        std::swap(deps, company.deps);
    }

    void Company::add_emp(Employee & emp, const std::string &dep_name) {
        std::pair<int, Employee *> pair = {count, &emp};
        std::vector<std::pair<int, Employee *>> my_table = get_table();
        my_table.push_back(pair);
        std::sort(my_table.begin(), my_table.end());
        //add_to_dep(emp, get_dep(dep_name));
        std::vector<Department> a;
        Company depr(get_dep(get_name()), a);
        ++count;
    }

    //void Company::add_to_dep(Employee &emp, Department &dep) {
      //  dep.get_table()
    //}




    /*Superuser & Superuser::operator =(Superuser const &superuser) {
        if (this == &superuser) return *this;
        Superuser(superuser).swap(*this);
        return *this;
    }*/

    Department *Superuser::get_dep() {
        return dep;
    }

    void Superuser::set_dep(Department *new_dep) {
        dep = new_dep;
    }

    Superuser::Superuser(Superuser &&superuser) noexcept {
        swap(superuser);
    }

    Superuser & Superuser::operator =(Superuser &&superuser) noexcept {
        swap(superuser);
        return *this;
    }

    void Superuser::swap(Superuser &superuser) {
        std::string tmp = get_name();
        set_name(superuser.get_name());
        superuser.set_name(std::move(tmp));
        tmp = get_education();
        set_education(superuser.get_education());
        superuser.set_education(std::move(tmp));
        tmp = get_birth_year();
        set_birth_year(superuser.get_birth_year());
        superuser.set_birth_year(std::move(tmp));
        tmp = get_post();
        set_post(superuser.get_post());
        superuser.set_post(std::move(tmp));
        float tmp0 = get_salary();
        set_salary(superuser.get_salary());
        superuser.set_salary(tmp0);
        std::swap(dep, superuser.dep);
    }
}