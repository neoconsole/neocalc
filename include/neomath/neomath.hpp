#pragma once

#include "external/exprtk.hpp"
#include <cmath>
#include <stdexcept>
#include <string>

template <typename T>
concept NumericType =
    std::is_arithmetic_v<T> && !std::is_same_v<T, bool> && !std::is_same_v<T, char> &&
    !std::is_same_v<T, signed char> && !std::is_same_v<T, unsigned char>;

template <NumericType T>
// NOLINTNEXTLINE(readability-identifier-naming)
class neomath {
public:
  neomath<T>() { m_symbolTable.add_function("root", root); }

  auto compile(const std::string &expr) -> T {
    m_expression.register_symbol_table(m_symbolTable);
    if (!m_parser.compile(expr, m_expression)) {
      throw std::runtime_error("Failed to compile: " + expr);
    }
    return m_expression.value();
  }

  void defineVariable(const std::string &name, const T &value) {
    m_symbolTable.add_variable(name, value);
  }

  void addFunction(const std::string &name, T (*function)(T, T)) {
    m_symbolTable.add_function(name, function);
  }

  static auto root(T value, T n) -> T {
    if (value < 0 && std::fmod(n, 2) != 0) {
      // For odd roots of negative numbers
      return -std::pow(-value, T(1) / n);
    }
    return std::pow(value, T(1) / n);
  }

private:
  exprtk::expression<T> m_expression;
  exprtk::parser<T> m_parser;
  exprtk::symbol_table<T> m_symbolTable;
};
