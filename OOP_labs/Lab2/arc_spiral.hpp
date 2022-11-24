#include <iostream>
#include <cmath>

namespace arc_spiral {

class Arc_spiral {
    public: 
        Arc_spiral(float k) : k(k)
        {}
        Arc_spiral & set_k(float k);
        float get_k() const;
        float distance(float phi) const;
        float seg_square(float r1, float r2) const;
        float coil_square(float n) const;
        float ring_square(float n) const;
        float arc_len(float phi) const;
        float curv_radius(float phi) const;
    private:
        float k;
};

void menu();
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
void get_parameter(float &k);

}