#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "arc_spiral.hpp"

TEST_CASE("Constructor") {
    int k = 15;
    arc_spiral::Arc_spiral as(k);
    REQUIRE(as.get_k() == k);
}

TEST_CASE("Setter") {
    int k = 15;
    arc_spiral::Arc_spiral as(k);
    as.set_k(32);
    REQUIRE(as.get_k() == 32);
}

TEST_CASE("Math") {
    const double err = 0.00001;
    int k = 15;
    float phi = 3;
    float r1 = 2;
    float r2 = 88;
    float n = 10;
    arc_spiral::Arc_spiral as(k);
    REQUIRE(abs(45 - as.distance(phi)) <= err);
    REQUIRE(abs(6603.33 - as.seg_square(r1, r2)) <= err);
    REQUIRE(abs(283.791 - as.coil_square(n)) <= err);
    REQUIRE(abs(84.7896 - as.arc_len(phi)) <= err);
    REQUIRE(abs(43.122 - as.curv_radius(phi)) <= err);
}