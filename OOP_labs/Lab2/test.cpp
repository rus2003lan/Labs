#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "arc_spiral.hpp"

TEST_CASE("Constructor") {
    int k = 15;
    arc_spiral::Arc_spiral as(k);
    arc_spiral::Arc_spiral as2(k + 21);
    arc_spiral::Arc_spiral as3(k + 34);
    REQUIRE(as.get_k() == k);
    REQUIRE(as2.get_k() == k + 21);
    REQUIRE(as3.get_k() == k + 34);
}

TEST_CASE("Setter") {
    int k = 15;
    arc_spiral::Arc_spiral as(k);
    as.set_k(32);
    REQUIRE(as.get_k() == 32);
    as.set_k(190);
    REQUIRE(as.get_k() == 190);
    as.set_k(2);
    REQUIRE(as.get_k() == 2);
}

TEST_CASE("Math") {
    const double err = 0.00001;
    int k1 = 15;
    float phi1 = 3;
    float r11 = 2;
    float r21 = 88;
    float n1 = 10;
    arc_spiral::Arc_spiral as(k1);
    REQUIRE(abs(45 - as.distance(phi1)) <= err);
    REQUIRE(abs(6603.33 - as.seg_square(r11, r21)) <= err);
    REQUIRE(abs(283.791 - as.coil_square(n1)) <= err);
    REQUIRE(abs(84.7896 - as.arc_len(phi1)) <= err);
    REQUIRE(abs(43.122 - as.curv_radius(phi1)) <= err);
    int k2 = 15; // доделай тесты
    float phi2 = 3;
    float r12 = 2;
    float r22 = 88;
    float n2 = 10;
    arc_spiral::Arc_spiral as(k2);
    REQUIRE(abs(45 - as.distance(phi2)) <= err);
    REQUIRE(abs(6603.33 - as.seg_square(r12, r22)) <= err);
    REQUIRE(abs(283.791 - as.coil_square(n2)) <= err);
    REQUIRE(abs(84.7896 - as.arc_len(phi2)) <= err);
    REQUIRE(abs(43.122 - as.curv_radius(phi2)) <= err);
}