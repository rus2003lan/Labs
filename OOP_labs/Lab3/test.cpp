#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "number16.hpp"

TEST_CASE("Constructor") {
    number16::Number16 a = 8;
    number16::Number16 b = -8;
    number16::Number16 c = "1000000000000000000000000001000";
    number16::Number16 d = "0000000000000000000000000001000";
    char a1 [31] = ""; // тут должен быть hex
    char b1 [31] = ""; // тут должен быть hex
    int c1 = -8;
    int d1 = 8;
    REQUIRE(!(compare(a.get_number16(), a1)));
    REQUIRE(!(compare(b.get_number(), b1)));
    REQUIRE(c1 == c.get_number10());
    REQUIRE(d1 == d.get_number10());
}

TEST_CASE("Arithmetic") {
    number16::Number16 a = 8;
    number16::Number16 b = 10;
    number16::Number16 c = -38;
    number16::Number16 d = -212;
    number16::Number16 a_b = 18;
    number16::Number16 c_d = -250;
    number16::Number16 b_c = -28;
    number16::Number16 d = -212;
    REQUIRE(a + b, a_b);
}

TEST_CASE("Compare") {
    number16::Number16 a = 8;
    number16::Number16 b = 10;
    number16::Number16 c = -38;
    number16::Number16 d = -212;
    number16::Number16 e = -212;
    number16::Number16 d = 10;
    REQUIRE(a < b);
    REQUIRE(c < a);
    REQUIRE(d < c);
    REQUIRE(c <= a);
    REQUIRE(a <= b);
    REQUIRE(d <= e);
    REQUIRE(a != b);
    REQUIRE(c != a);
    REQUIRE(d != e);
    REQUIRE(!(b != d));
    REQUIRE(b == d);
    REQUIRE(d == b);
    REQUIRE(!(a == b));
    REQUIRE(!(c == d));
    REQUIRE(d == e);
    REQUIRE(e == d);
    REQUIRE(b >= a);
    REQUIRE(c >= d);
    REQUIRE(b >= c);
    REQUIRE(d >= e);
    REQUIRE(b >= d);
}