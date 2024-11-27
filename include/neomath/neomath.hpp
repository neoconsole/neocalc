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
    m_symbolTable.add_constant("e", M_E);
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

  void clear() { m_symbolTable.clear(); }

private:
  exprtk::expression<T> m_expression;
  exprtk::parser<T> m_parser;
  exprtk::symbol_table<T> m_symbolTable;
};
