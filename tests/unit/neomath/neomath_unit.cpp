#include "../../../include/neomath/neomath.hpp"
#include <catch2/catch_all.hpp>
#include <catch2/matchers/catch_matchers.hpp>
#include <cmath>

namespace {
neomath<double> math;
}

TEST_CASE("Compile and evaluate expressions", "[compile]") {
  SECTION("Basic arithmetic") {
    REQUIRE(math.compile("2 + 3") == 5);
    REQUIRE(math.compile("10 - 4") == 6);
    REQUIRE(math.compile("3 * 4") == 12);
    REQUIRE(math.compile("15 / 3") == 5);
  }

  SECTION("Use of pi constant") {
    REQUIRE_THAT(math.compile("pi"), Catch::Matchers::WithinRel(M_PI, 0.0000001));
    REQUIRE_THAT(math.compile("2 * pi"), Catch::Matchers::WithinRel(M_PI * 2, 0.0000001));
  }

  SECTION("Use of golden ratio constant") {
    REQUIRE_THAT(math.compile("gr"), Catch::Matchers::WithinRel(1.61803398875, 0.0000001));
    REQUIRE_THAT(math.compile("2 * gr"), Catch::Matchers::WithinRel(3.23606797749, 0.0000001));
  }

  SECTION("Use of eulers number constant") {
    REQUIRE_THAT(math.compile("e"), Catch::Matchers::WithinRel(M_E, 0.0000001));
    REQUIRE_THAT(math.compile("2 * e"), Catch::Matchers::WithinRel(M_E * 2, 0.0000001));
  }

  SECTION("Complex expressions") {
    REQUIRE_THAT(
        math.compile("2 * pi + root(16, 2)"), Catch::Matchers::WithinRel(10.28318530718, 0.0000001)
    );
    REQUIRE_THAT(
        math.compile("gr * root(27, 3)"), Catch::Matchers::WithinRel(4.85410196624, 0.0000001)
    );
    REQUIRE_THAT(
        math.compile("(pi * sqrt(10)) / e"), Catch::Matchers::WithinRel(3.65473077949, 0.0000001)
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
