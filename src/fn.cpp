#include "fn.h"
#include "error.h"
#include "type.h"
#include "value.h"
#include <cstdint>
#include <iostream>

using namespace liscpp;

// Constructors

Fn::Fn(GcString *name, Value (*f)())
    : m_name{name}, m_captures{new GcVector()}, m_arity{0}, m_type{FnType::Fn0},
      m_fn{.fn0 = f} {}

Fn::Fn(GcString *name, Value (*f)(Value))
    : m_name{name}, m_captures{new GcVector()}, m_arity{1}, m_type{FnType::Fn1},
      m_fn{.fn1 = f} {}

Fn::Fn(GcString *name, Value (*f)(Value, Value))
    : m_name{name}, m_captures{new GcVector()}, m_arity{2}, m_type{FnType::Fn2},
      m_fn{.fn2 = f} {}

Fn::Fn(GcString *name, Value (*f)(Value, Value, Value))
    : m_name{name}, m_captures{new GcVector()}, m_arity{3}, m_type{FnType::Fn3},
      m_fn{.fn3 = f} {}

Fn::Fn(GcString *name, Value (*f)(Value, Value, Value, Value))
    : m_name{name}, m_captures{new GcVector()}, m_arity{4}, m_type{FnType::Fn4},
      m_fn{.fn4 = f} {}

Fn::Fn(GcString *name, Value (*f)(Value, Value, Value, Value, Value))
    : m_name{name}, m_captures{new GcVector()}, m_arity{5}, m_type{FnType::Fn5},
      m_fn{.fn5 = f} {}

Fn::Fn(GcString *name, uint32_t arity, Value (*f)(const Value[], uint32_t))
    : m_name{name}, m_captures{new GcVector()}, m_arity{arity},
      m_type{FnType::FnAny}, m_fn{.fn_any = f} {}

Fn::Fn(GcString *name, GcVector *captures, uint32_t arity,
       Value (*f)(GcVector *, const Value[], uint32_t))
    : m_name{name}, m_captures{captures}, m_arity{arity}, m_type{FnType::FnAny},
      m_fn{.fn_closure = f} {}

// Overloads

Value Fn::operator()(const Value args[], uint32_t n) const {
  if (n < m_arity)
    throw __error__::new_arity_error(m_name, m_arity, n);

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
  case FnType::Closure:
    return m_fn.fn_closure(m_captures, args, n);
  }
}

void Fn::code_rep(std::ostream &os) const {
  os << "#<Fn::" << __type__::str(get_type()) << "(" << m_arity << ")"
     << get_name() << ">";
}

void Fn::display_rep(std::ostream &os) const { code_rep(os); }
