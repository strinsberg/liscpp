#include "value.h"
#include <cstdint>

// Fn methods /////////////////////////////////////////////////////////////////

// TODO This is not a freindly user error. It will either have to be caught
// elsewhere to provide extra information or an Fn will need to hold more
// information in order to give a better picture of the function when it
// is used wrong. Probably for starters a name might be useful if it is a
// named function. A function to create a nice external representation of the
// Fn object for display might also be good. For now this will work for testing
// but is not gonna be enough.

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

// Value methods //////////////////////////////////////////////////////////////

Value Value::Int(int64_t i) { return Value(i); }

// Will probably eventually just take an int or pointer to share strings
Value Value::Key(const std::string &s) {
  Value v;
  v.m_type = ValType::Key;
  v.m_val.s = new std::string(s);
  return v;
}

// Sort of a helper for when it is more convinient to work with a string literal
// unless I can convince myself that this way is as efficient as creating the
// string pointer first. The major reason for abstracting like this is that
// creating the pointer will have to use the gc_allocator to ensure the string
// contents are collectable.
Value Value::Str(const std::string &s) {
  Value v;
  v.m_type = ValType::Str;
  v.m_val.s = new std::string(s);
  return v;
}

// TODO these errors might also not be the best. It may be easier to do the
// checks in the core functions so that one can say things like
// "cannot apply: <value-rep>" without having to catch this error. Though it
// seems better to catch this error. The question might be whether we need to
// throw a proper lisp error or a C++ error just to indicate an error.
int64_t Value::get_int() const {
  if (is_int())
    return m_val.i;
  throw Error("Not an int", *this);
}

int64_t Value::get_flt() const {
  if (is_flt())
    return m_val.d;
  throw Error("Not a float", *this);
}

std::string *Value::get_str() const {
  if (is_str())
    return m_val.s;
  throw Error("Not a string", *this);
}

Fn *Value::get_fn() const {
  if (is_fn())
    return m_val.f;
  throw Error("not a function", *this);
}

Error *Value::get_error() const {
  if (is_err())
    return m_val.e;
  throw Error("Not an error", *this);
}

bool Value::operator==(const Value &other) const {
  switch (m_type) {
  case ValType::Int:
    return other.is_int() and as_int() == other.as_int();
  case ValType::Str:
    return other.is_str() and as_str() == other.as_str();
  case ValType::Fn:
    return other.is_fn() and as_fn() == other.as_fn();
  case ValType::Err:
    return other.is_err() and as_error() == other.as_error();
  default:
    return false;
  }
}

// Error methods //////////////////////////////////////////////////////////////

const char *Error::what() const throw() {
  return m_message.c_str(); // TODO also some rep of data
}
