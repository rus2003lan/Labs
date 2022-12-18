#include "company.hpp"

namespace company {

    Employee::Employee(const Employee &emp) {
        name = emp.name;
        birth_year = emp.birth_year;
        education = emp.education;
        post = emp.post;
        salary = emp.salary;
    }

    void Employee::to_super() {

    }

    std::string Employee::info() const{
        return name;
    }

    std::string Employee::get_post() const{
        return post;
    }

    void Employee::set_post(std::string post) {
        if(post != "Employee" || post != "Superuser") {
            throw std::invalid_argument("Incorrect post");
        }
        this->post = post;
    }

    float Employee::get_salary() const{
        return salary;
    }

    void Employee::set_salary(const float salary) {
        if (salary < 0) {
            throw std::invalid_argument("Salary < 0");
        }
        this->salary = salary;
    }
}