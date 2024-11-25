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

TEST_CASE("Compile and evaluate expressions", "[compile]") {
  SECTION("Basic arithmetic") {
    REQUIRE(math.compile("2 + 3") == 5);
    REQUIRE(math.compile("10 - 4") == 6);
    REQUIRE(math.compile("3 * 4") == 12);
    REQUIRE(math.compile("15 / 3") == 5);
  }

  SECTION("Use of pi constant") {
    REQUIRE_THAT(math.compile("pi"), Catch::Matchers::WithinRel(3.14159265359, 0.0000001));
    REQUIRE_THAT(math.compile("2 * pi"), Catch::Matchers::WithinRel(6.28318530718, 0.0000001));
  }

  SECTION("Use of golden ratio constant") {
    REQUIRE_THAT(math.compile("gr"), Catch::Matchers::WithinRel(1.61803398875, 0.0000001));
    REQUIRE_THAT(math.compile("2 * gr"), Catch::Matchers::WithinRel(3.23606797749, 0.0000001));
  }

  SECTION("Root function in expressions") {
    REQUIRE_THAT(math.compile("root(16, 2)"), Catch::Matchers::WithinRel(4.0, 0.0000001));
    REQUIRE_THAT(math.compile("root(27, 3)"), Catch::Matchers::WithinRel(3.0, 0.0000001));
    REQUIRE_THAT(math.compile("root(-8, 3)"), Catch::Matchers::WithinRel(-2.0, 0.0000001));
  }

  SECTION("Complex expressions") {
    REQUIRE_THAT(
        math.compile("2 * pi + root(16, 2)"), Catch::Matchers::WithinRel(10.28318530718, 0.0000001)
    );
    REQUIRE_THAT(
        math.compile("gr * root(27, 3)"), Catch::Matchers::WithinRel(4.85410196624, 0.0000001)
    );
  }
}

TEST_CASE("Variable definition and usage", "[variables]") {
  SECTION("Define and use variables") {
    math.defineVariable("x", 5);
    REQUIRE(math.compile("x") == 5);
    REQUIRE(math.compile("x + 3") == 8);
    REQUIRE(math.compile("2 * x") == 10);

    math.defineVariable("y", 2.5);
    REQUIRE_THAT(math.compile("x * y"), Catch::Matchers::WithinRel(12.5, 0.0000001));
  }
}

TEST_CASE("Custom function addition", "[custom_functions]") {
  SECTION("Add and use custom function") {
    auto customFunc = [](double a, double b) { return a * b + 1; };
    math.addFunction("customFunc", customFunc);

    REQUIRE(math.compile("customFunc(3, 4)") == 13);
    REQUIRE_THAT(math.compile("customFunc(2.5, 3)"), Catch::Matchers::WithinRel(8.5, 0.0000001));
  }
}

TEST_CASE("Error handling", "[errors]") {
  SECTION("Invalid expression compilation") {
    REQUIRE_THROWS_AS(math.compile("2 +"), std::runtime_error);
    REQUIRE_THROWS_AS(math.compile("root(4)"), std::runtime_error);
  }
}
