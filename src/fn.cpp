#include "fn.h"
#include "error.h"
#include "value.h"
#include <cstdint>
#include <format>
#include <stdexcept>

Value Fn::operator()(const Value args[], uint32_t n) {
  if (n < m_arity)
    throw std::out_of_range(std::format(
        "must have at least m_arity number or arguments: Expected {}: Got {}",
        m_arity, n));

  switch (m_type) {
  case FnType::Fn0:
    return m_fn.fn0();
  case FnType::Fn1:
    return m_fn.fn1(args[0]);
  case FnType::Fn2:
    return m_fn.fn2(args[0], args[1]);
  case FnType::Fn3:
    return m_fn.fn3(args[0], args[1], args[2]);
  case FnType::Fn4:
    return m_fn.fn4(args[0], args[1], args[2], args[3]);
  case FnType::Fn5:
    return m_fn.fn5(args[0], args[1], args[2], args[3], args[4]);
  case FnType::FnAny:
    return m_fn.fn_any(args, n);
  default:
    throw std::invalid_argument(std::format(
        "Fn::operator() encountered uncovered type: Got type (as int) {}",
        int(m_type)));
  }
}

bool Fn::operator==(const Fn &other) const {
  switch (m_type) {
  case FnType::Fn0:
    return other.m_type == FnType::Fn0 and m_fn.fn0 == other.m_fn.fn0;
  case FnType::Fn1:
    return other.m_type == FnType::Fn1 and m_fn.fn1 == other.m_fn.fn1;
  case FnType::Fn2:
    return other.m_type == FnType::Fn2 and m_fn.fn2 == other.m_fn.fn2;
  case FnType::Fn3:
    return other.m_type == FnType::Fn3 and m_fn.fn3 == other.m_fn.fn3;
  case FnType::Fn4:
    return other.m_type == FnType::Fn4 and m_fn.fn4 == other.m_fn.fn4;
  case FnType::Fn5:
    return other.m_type == FnType::Fn5 and m_fn.fn5 == other.m_fn.fn5;
  case FnType::FnAny:
    return other.m_type == FnType::FnAny and m_fn.fn_any == other.m_fn.fn_any;
  default:
    throw std::invalid_argument(std::format(
        "Fn::operator== encountered uncovered type: Got type (as int) {}",
        int(m_type)));
  }
}
