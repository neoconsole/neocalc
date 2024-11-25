#pragma once

#include "external/exprtk.hpp"
#include <cmath>
#include <stdexcept>
#include <string>
#include <type_traits>

template <typename T>
concept NumericType =
    std::is_arithmetic_v<T> && !std::is_same_v<T, bool> && !std::is_same_v<T, char> &&
    !std::is_same_v<T, signed char> && !std::is_same_v<T, unsigned char>;

template <NumericType T>
// NOLINTNEXTLINE(readability-identifier-naming)
class neomath {
public:
  neomath<T>() {
    m_symbolTable.add_pi();
    m_symbolTable.add_constant("gr", (1.0 + std::sqrt(5.0)) / 2.0);
    m_symbolTable.add_function("root", root);
  }

  auto compile(const std::string &expr) -> T {
    m_expression.register_symbol_table(m_symbolTable);
    if (!m_parser.compile(expr, m_expression)) {
      throw std::runtime_error("Exprtk: " + m_parser.error());
    }
    return m_expression.value();
  }

  void defineVariable(const std::string &name, const T &value) {
    auto &valueRef = const_cast<std::remove_const_t<T> &>(value);
    m_symbolTable.add_variable(name, valueRef);
  }

  void addFunction(const std::string &name, T (*function)(T, T)) {
    m_symbolTable.add_function(name, function);
  }

  constexpr static auto root(T value, T n) -> T {
    if (n == 0) { throw std::domain_error("Root with zero degree is undefined."); }
    if (value < 0) {
      if (std::floor(n) == n) {
        if (static_cast<int>(n) % 2 != 0) { return -std::pow(-value, T(1) / n); }
        return std::numeric_limits<T>::quiet_NaN();
      }
      return std::numeric_limits<T>::quiet_NaN();
    }
    return std::pow(value, T(1) / n);
  }

private:
  exprtk::expression<T> m_expression;
  exprtk::parser<T> m_parser;
  exprtk::symbol_table<T> m_symbolTable;
};
