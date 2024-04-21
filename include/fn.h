#ifndef LISCPP_FN_H
#define LISCPP_FN_H

#include "value.h"
#include <cstdint>

enum class FnType {
  Fn0,
  Fn1,
  Fn2,
  Fn3,
  Fn4,
  Fn5,
  FnAny,
};

union FnUnion {
  FnUnion(Value (*f)()) : fn0{f} {}
  FnUnion(Value (*f)(Value)) : fn1{f} {}
  FnUnion(Value (*f)(Value, Value)) : fn2{f} {}
  FnUnion(Value (*f)(Value, Value, Value)) : fn3{f} {}
  FnUnion(Value (*f)(Value, Value, Value, Value)) : fn4{f} {}
  FnUnion(Value (*f)(Value, Value, Value, Value, Value)) : fn5{f} {}
  FnUnion(Value (*f)(const Value[], uint32_t)) : fn_any{f} {}

  Value (*fn0)();
  Value (*fn1)(Value);
  Value (*fn2)(Value, Value);
  Value (*fn3)(Value, Value, Value);
  Value (*fn4)(Value, Value, Value, Value);
  Value (*fn5)(Value, Value, Value, Value, Value);
  Value (*fn_any)(const Value[], uint32_t);
};

class Fn {
public:
  Fn(Value (*f)()) : m_type{FnType::Fn0}, m_fn{f} {}
  Fn(Value (*f)(Value)) : m_type{FnType::Fn1}, m_fn{f} {}
  Fn(Value (*f)(Value, Value)) : m_type{FnType::Fn2}, m_fn{f} {}
  Fn(Value (*f)(Value, Value, Value)) : m_type{FnType::Fn3}, m_fn{f} {}
  Fn(Value (*f)(Value, Value, Value, Value)) : m_type{FnType::Fn4}, m_fn{f} {}
  Fn(Value (*f)(Value, Value, Value, Value, Value))
      : m_type{FnType::Fn5}, m_fn{f} {}
  Fn(Value (*f)(const Value[], uint32_t)) : m_type{FnType::FnAny}, m_fn{f} {}

  Value operator()(const Value[], uint32_t n);
  bool operator==(const Fn &other) const;

private:
  FnType m_type;
  FnUnion m_fn;
};

#endif
