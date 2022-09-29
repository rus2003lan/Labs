#include "arc_spiral.hpp"

namespace arc_spiral {

void menu() {
    int check = 0;
    float k = 0;
    float phi = 0;
    float r1 = 0;
    float r2 = 0;
    float n = 0;
    std::cout << "Enter the parameter k for the archimedean spiral: ";
    get_parameter(k);
    Arc_spiral as(k);
    while (check != 9) {
        std::cout << "Choose what you want to do with the archimedean spiral: " << std::endl;
        std::cout << "1)Get k" << std::endl;
        std::cout << "2)Set k" << std::endl;
        std::cout << "3)Distance" << std::endl;
        std::cout << "4)Segment square" << std::endl;
        std::cout << "5)Coil square" << std::endl;
        std::cout << "6)Ring square" << std::endl;
        std::cout << "7)Spiral length" << std::endl;
        std::cout << "8)Curve radius" << std::endl;
        std::cout << "9)Exit" << std::endl;
        getnumber(check);
        while (true) {
            if(check < 1 || check > 9) {
                std::cout << "Repeat input:" << std::endl;
                getnumber(check);
            }
            else break;
        }
        if (check == 1) {
            std::cout << "Parameter k: " << as.get_k() << std::endl;
        }
        else if (check == 2) {
            std::cout << "Input new parameter k:" << std::endl;
            get_parameter(k);
            as.set_k(k);
        }
        else if (check == 3) {
            std::cout << "Input angle phi:" << std::endl;
            get_parameter(phi);
            std::cout << "Distance: " << as.distance(phi) << std::endl;
        }
        else if (check == 4) {
            std::cout << "Input r1:" << std::endl;
            get_parameter(r1);
            std::cout << "Input r2:" << std::endl;
            get_parameter(r2);
            std::cout << "Segment square: " << as.seg_square(r1, r2) << std::endl;
        }
        else if (check == 5) {
            std::cout << "Input n:" << std::endl;
            get_parameter(n);
            std::cout << "Coil square: " << as.coil_square(n) << std::endl;
        }
        else if (check == 6) {
            std::cout << "Input n:" << std::endl;
            get_parameter(n);
            std::cout << "Ring square: " << as.ring_square(n) << std::endl;
        }
        else if (check == 7) {
            std::cout << "Input angle phi:" << std::endl;
            get_parameter(phi);
            std::cout << "Spiral length: " << as.arc_len(phi) << std::endl;
        }
        else if (check == 8) {
            std::cout << "Input angle phi:" << std::endl;
            get_parameter(phi);
            std::cout << "Curve radius: " << as.curv_radius(phi) << std::endl;
        }
    }
}

void get_parameter(float &par) {
    getnumber(par);
    while (par <= 0) {
        std::cout << "Uncorrect parameter (help: parameter > 0). Repeat input: " << std::endl;
        getnumber(par);
    }
}

Arc_spiral & Arc_spiral::set_k(float k) {
    this->k = k;
    return *this;
}
float Arc_spiral::get_k() {
    return k;
}
float Arc_spiral::distance(float phi) {
    return k * phi;
}
float Arc_spiral::seg_square(float r1, float r2) {
    float phi = abs(r1 / k - r2 / k);
    return phi * (pow(r1, 2) + pow(r2, 2) + r1 * r2) / 6;
}
float Arc_spiral::coil_square(float n) {
    return M_PI * (pow(n, 2) + n * (n -1) + pow(n - 1, 2)) / 3;
}
float Arc_spiral::ring_square(float n) {
    return 2 * n * M_PI;
}
float Arc_spiral::arc_len(float phi) {
    return k / 2 * (phi * sqrt(pow(phi, 2) + 1) + std::log(phi + sqrt(pow(phi, 2) + 1)));
}
float Arc_spiral::curv_radius(float phi) {
    return k * pow(pow(phi, 2) + 1, 1.5) / (pow(phi, 2) + 2);
}

}