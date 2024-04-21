#include "fn.h"
#include "error.h"
#include "value.h"

// TODO these may not have user friendly errors yet

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
  }

  // TODO I should probably deal with this in apply to give a better error.
  // If the outer functions do the job this could be impossible to run into
  // here.
  // Or this function needs to deal with the error in a way that makes it
  // easy for the user to see, perhaps with extra function information and
  // the rep for functions being defined for Fn and just used for Value.
  throw Error("Function application error", Value(this));
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
    return false;
  }
}
