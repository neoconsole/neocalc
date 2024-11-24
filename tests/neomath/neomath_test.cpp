#include "../../include/neomath/neomath.hpp"
#include <catch2/catch_all.hpp>
#include <cmath>

namespace {
neomath<double> math;
}

TEST_CASE("Root operations", "[root]") {
  SECTION("Basic square root operations") {
    REQUIRE_THAT(math.root(4, 2), Catch::Matchers::WithinRel(2.0, 0.0001));
    REQUIRE_THAT(math.root(16, 2), Catch::Matchers::WithinRel(4.0, 0.0001));
    REQUIRE_THAT(math.root(6, 2), Catch::Matchers::WithinRel(2.449489743, 0.0001));
  }

  SECTION("Cube root operations") {
    REQUIRE_THAT(math.root(8, 3), Catch::Matchers::WithinRel(2.0, 0.0001));
    REQUIRE_THAT(math.root(27, 3), Catch::Matchers::WithinRel(3.0, 0.0001));
    REQUIRE_THAT(math.root(100, 3), Catch::Matchers::WithinRel(4.641588834, 0.0001));
  }

  SECTION("Fourth root operations") {
    REQUIRE_THAT(math.root(16, 4), Catch::Matchers::WithinRel(2.0, 0.0001));
    REQUIRE_THAT(math.root(81, 4), Catch::Matchers::WithinRel(3.0, 0.0001));
    REQUIRE_THAT(math.root(50, 4), Catch::Matchers::WithinRel(2.659240142, 0.0001));
  }

  SECTION("Odd roots and negative numbers") {
    REQUIRE_THAT(math.root(-8, 3), Catch::Matchers::WithinRel(-2.0, 0.0001));
    REQUIRE_THAT(math.root(-27, 3), Catch::Matchers::WithinRel(-3.0, 0.0001));
    REQUIRE_THAT(math.root(-125, 5), Catch::Matchers::WithinRel(-2.6265281, 0.0001));
  }

  SECTION("Even roots of negative numbers") {
    REQUIRE(std::isnan(math.root(-4, 2)));
    REQUIRE(std::isnan(math.root(-16, 4)));
  }

  SECTION("Fractional roots") {
    REQUIRE_THAT(math.root(16, 0.5), Catch::Matchers::WithinRel(256.0, 0.0001));
    REQUIRE_THAT(math.root(27, 1.0 / 3.0), Catch::Matchers::WithinRel(19683.0, 0.0001));
  }

  SECTION("Edge cases") {
    REQUIRE_THAT(math.root(0, 2), Catch::Matchers::WithinRel(0.0, 0.0001));
    REQUIRE_THAT(math.root(0, 3), Catch::Matchers::WithinRel(0.0, 0.0001));
    REQUIRE_THAT(math.root(1, 2), Catch::Matchers::WithinRel(1.0, 0.0001));
    REQUIRE_THAT(math.root(1, 3), Catch::Matchers::WithinRel(1.0, 0.0001));
    REQUIRE_THAT(math.root(1, 4), Catch::Matchers::WithinRel(1.0, 0.0001));
  }

  SECTION("Large numbers") {
    REQUIRE_THAT(math.root(1000000, 2), Catch::Matchers::WithinRel(1000.0, 0.0001));
    REQUIRE_THAT(math.root(1000000, 3), Catch::Matchers::WithinRel(100.0, 0.0001));
  }

  SECTION("Small numbers") {
    REQUIRE_THAT(math.root(0.0001, 2), Catch::Matchers::WithinRel(0.01, 0.0001));
    REQUIRE_THAT(math.root(0.0001, 3), Catch::Matchers::WithinRel(0.0464158883, 0.0001));
  }

  SECTION("Properties of roots") {
    double x = 5.0;
    double n = 3.0;
    double powered = std::pow(x, n);
    REQUIRE_THAT(math.root(powered, n), Catch::Matchers::WithinRel(x, 0.0001));

    double a = 3.0;
    double powered_a = std::pow(a, 4);
    REQUIRE_THAT(math.root(powered_a, 4), Catch::Matchers::WithinRel(a, 0.0001));
  }

  SECTION("Negative numbers with odd roots") {
    REQUIRE_THAT(math.root(-8, 3), Catch::Matchers::WithinRel(-2.0, 0.0001));
    REQUIRE_THAT(math.root(-1000000, 3), Catch::Matchers::WithinRel(-100.0, 0.0001));
    REQUIRE_THAT(math.root(-0.0001, 3), Catch::Matchers::WithinRel(-0.0464158883, 0.0001));
  }
}
