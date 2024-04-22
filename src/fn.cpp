#include "fn.h"
#include "error.h"
#include "value.h"
#include <cstdint>
#include <format>

uint32_t Fn::min_args() const {
  switch (m_type) {
  case FnType::Fn0:
    return 0;
  case FnType::Fn1:
    return 1;
  case FnType::Fn2:
    return 2;
  case FnType::Fn3:
    return 3;
  case FnType::Fn4:
    return 4;
  case FnType::Fn5:
    return 5;
  case FnType::FnAny:
    return 0;
  default:
    throw Panic(std::format("Fn::operator== encountered uncovered type {}",
                            int(m_type)));
  }
}

Value Fn::operator()(const Value args[], uint32_t n) {
  switch (m_type) {
  case FnType::Fn0:
    if (n >= 0) // TODO should calling a function with too many args error?
      return m_fn.fn0();
    break;
  case FnType::Fn1:
    if (n >= 1)
      return m_fn.fn1(args[0]);
    break;
  case FnType::Fn2:
    if (n >= 2)
      return m_fn.fn2(args[0], args[1]);
    break;
  case FnType::Fn3:
    if (n >= 3)
      return m_fn.fn3(args[0], args[1], args[2]);
    break;
  case FnType::Fn4:
    if (n >= 4)
      return m_fn.fn4(args[0], args[1], args[2], args[3]);
    break;
  case FnType::Fn5:
    if (n >= 5)
      return m_fn.fn5(args[0], args[1], args[2], args[3], args[4]);
    break;
  case FnType::FnAny:
    return m_fn.fn_any(args, n);
  default:
    throw Panic(
        std::format("Fn::apply encountered uncovered type {}", int(m_type)));
  }

  // TODO use function name when Fn has more fields
  throw ArityError("anonymous", min_args(), n);
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
    throw Panic(std::format("Fn::operator== encountered uncovered type {}",
                            int(m_type)));
  }
}
