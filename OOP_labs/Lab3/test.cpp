#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "number16.hpp"

/*TEST_CASE("Constructor") {
    number16::Number16 a = 8;
    number16::Number16 b = -8;
    number16::Number16 c("100000000000000000000000000100");
    number16::Number16 d("000000000000000000000000000100");
    char a1 [31] = ""; // тут должен быть hex
    char b1 [31] = ""; // тут должен быть hex
    int c1 = -8;
    int d1 = 8;
    REQUIRE(!(compare(a.get_number16(), a1)));
    REQUIRE(!(compare(b.get_number(), b1)));
    REQUIRE(c1 == c.get_number10());
    REQUIRE(d1 == d.get_number10());
}*/

TEST_CASE("Arithmetic") {
    number16::Number16 a = 8;
    number16::Number16 b = 10;
    number16::Number16 b3 = 100;
    number16::Number16 c = -38;
    number16::Number16 c_b3 = 62;
    number16::Number16 d = -212;
    number16::Number16 a_b = 18;
    number16::Number16 c_d = -250;
    number16::Number16 b_c = -28;
    number16::Number16 d2 = -212;
    REQUIRE(a + b == a_b);
    REQUIRE(c + d == c_d);
    REQUIRE(b + c == b_c);
    REQUIRE(b3 + c == c_b3);
    REQUIRE(a_b - a == b);
    REQUIRE(a_b - b == a);
    REQUIRE(c_d - d == c);
    REQUIRE(c_d - c == d);
    REQUIRE(b_c - c == b);
    REQUIRE(b_c - b == c);
    REQUIRE(c_b3 - b3 == c);
    REQUIRE(c_b3 - c == b3);
}

TEST_CASE("Compare") {
    number16::Number16 a = 8;
    number16::Number16 b = 10;
    number16::Number16 be = 10;
    number16::Number16 r = -3;
    number16::Number16 c = -38;
    number16::Number16 h = 38;
    number16::Number16 d = -212;
    number16::Number16 e = -212;
    number16::Number16 d2 = 10;
    REQUIRE(b > a);
    REQUIRE(!(b > be));
    REQUIRE(a > c);
    REQUIRE(c > d);
    REQUIRE(h > c);
    REQUIRE(a < b);
    REQUIRE(c < a);
    REQUIRE(!(d < d));
    REQUIRE(c < h);
    REQUIRE(d < c);
    REQUIRE(r < a);
    REQUIRE(c <= a);
    REQUIRE(b <= be);
    REQUIRE(a <= b);
    REQUIRE(d <= e);
    REQUIRE(a != b);
    REQUIRE(c != a);
    REQUIRE(!(d != e));
    REQUIRE(b != d);
    REQUIRE(c != h);
    REQUIRE(e == d);
    REQUIRE(d == e);
    REQUIRE(!(a == b));
    REQUIRE(!(c == d));
    REQUIRE(be == b);
    REQUIRE(b == be);
    REQUIRE(!(c == h));
    REQUIRE(d == e);
    REQUIRE(e == d);
    REQUIRE(b >= a);
    REQUIRE(c >= d);
    REQUIRE(b >= c);
    REQUIRE(d >= e);
    REQUIRE(b >= be);
}