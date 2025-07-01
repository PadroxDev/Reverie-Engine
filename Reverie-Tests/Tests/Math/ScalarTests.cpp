#include <Catch2/catch_amalgamated.hpp>
#include <ReverieEngine.h>

using namespace Catch;
using namespace rev;

TEST_CASE("Math::Sqrt behaves correctly", "[Math][Sqrt]") {
    REQUIRE(Math::Sqrt(4.0f) == Approx(2.0f));
    REQUIRE(Math::Sqrt(0.0f) == Approx(0.0f));
    REQUIRE(Math::Sqrt(9.0f) == Approx(3.0f));
    REQUIRE(Math::Sqrt(1.0f) == Approx(1.0f));
    REQUIRE(std::isnan(Math::Sqrt(-1.0f)));  // or whatever behavior you expect on negatives
}

TEST_CASE("Math::Pow behaves correctly", "[Math][Pow]") {
    REQUIRE(Math::Pow(2.0f, 3.0f) == Approx(8.0f));
    REQUIRE(Math::Pow(5.0f, 0.0f) == Approx(1.0f));
    REQUIRE(Math::Pow(2.0f, -2.0f) == Approx(0.25f));
    REQUIRE(Math::Pow(-2.0f, 3.0f) == Approx(-8.0f));
}

TEST_CASE("Math::Log behaves correctly", "[Math][Log]") {
    REQUIRE(Math::Log(1.0f) == Approx(0.0f));
    REQUIRE(Math::Log(Math::E) == Approx(1.0f));
    REQUIRE(Math::Log(0.0f) == Approx(-INFINITY));
}