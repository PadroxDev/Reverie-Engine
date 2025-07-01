#define CATCH_CONFIG_MAIN
#include <Catch2/catch_amalgamated.hpp>

TEST_CASE("Minimal test", "[minimal]") {
    REQUIRE(1 == 1);
}