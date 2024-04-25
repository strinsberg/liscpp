#ifndef LISCPP_FN_H
#define LISCPP_FN_H

#include "type.h"
#include "value.h"
#include <cstdint>

const std::string no_name = "anonymous";

class Fn {
public:
  // Constructors overloaded for function arity
  Fn(GcString *name, Value (*f)())
      : m_name{name}, m_arity{0}, m_type{FnType::Fn0}, m_fn{.fn0 = f} {}
  Fn(GcString *name, Value (*f)(Value))
      : m_name{name}, m_arity{1}, m_type{FnType::Fn1}, m_fn{.fn1 = f} {}
  Fn(GcString *name, Value (*f)(Value, Value))
      : m_name{name}, m_arity{2}, m_type{FnType::Fn2}, m_fn{.fn2 = f} {}
  Fn(GcString *name, Value (*f)(Value, Value, Value))
      : m_name{name}, m_arity{3}, m_type{FnType::Fn3}, m_fn{.fn3 = f} {}
  Fn(GcString *name, Value (*f)(Value, Value, Value, Value))
      : m_name{name}, m_arity{4}, m_type{FnType::Fn4}, m_fn{.fn4 = f} {}
  Fn(GcString *name, Value (*f)(Value, Value, Value, Value, Value))
      : m_name{name}, m_arity{5}, m_type{FnType::Fn5}, m_fn{.fn5 = f} {}
  Fn(GcString *name, uint32_t arity,
     Value (*f)(const Value[], uint32_t))
      : m_name{name}, m_arity{arity}, m_type{FnType::FnAny}, m_fn{.fn_any = f} {
  }

  // Constructors overloaded for anonymous functions
  Fn(Value (*f)()) : Fn(new GcString(no_name), f) {}
  Fn(Value (*f)(Value)) : Fn(new GcString(no_name), f) {}
  Fn(Value (*f)(Value, Value)) : Fn(new GcString(no_name), f) {}
  Fn(Value (*f)(Value, Value, Value)) : Fn(new GcString(no_name), f) {}
  Fn(Value (*f)(Value, Value, Value, Value)) : Fn(new GcString(no_name), f) {}
  Fn(Value (*f)(Value, Value, Value, Value, Value)) : Fn(new GcString(no_name), f) {}
  Fn(uint32_t arity, Value (*f)(const Value[], uint32_t))
      : Fn(new GcString(no_name), arity, f) {}

  // Accessors
  inline const GcString &get_name() const { return *m_name; }
  inline uint32_t get_arity() const { return m_arity; }
  inline FnType get_type() const { return m_type; }

  // Operator overloads
  bool operator==(const Fn &other) const;
  Value operator()(const Value[], uint32_t n); // ArityError if n < arity

private:
  GcString* m_name;
  uint32_t m_arity;
  FnType m_type;

  union {
    Value (*fn0)();
    Value (*fn1)(Value);
    Value (*fn2)(Value, Value);
    Value (*fn3)(Value, Value, Value);
    Value (*fn4)(Value, Value, Value, Value);
    Value (*fn5)(Value, Value, Value, Value, Value);
    Value (*fn_any)(const Value[], uint32_t);
  } m_fn;
};

#endif
