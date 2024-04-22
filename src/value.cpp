#include "value.h"
#include "error.h"
#include "fn.h"
#include <cstdint>

// Constructors ///////////////////////////////////////////////////////////////

Value::Value(Value (*f)()) : m_type{ValType::Fn}, m_val{new Fn(f)} {}

Value::Value(Value (*f)(Value)) : m_type{ValType::Fn}, m_val{new Fn(f)} {}

Value::Value(Value (*f)(Value, Value))
    : m_type{ValType::Fn}, m_val{new Fn(f)} {}

Value::Value(Value (*f)(Value, Value, Value))
    : m_type{ValType::Fn}, m_val{new Fn(f)} {}

Value::Value(Value (*f)(Value, Value, Value, Value))
    : m_type{ValType::Fn}, m_val{new Fn(f)} {}

Value::Value(Value (*f)(Value, Value, Value, Value, Value))
    : m_type{ValType::Fn}, m_val{new Fn(f)} {}

Value::Value(Value (*f)(const Value[], uint32_t))
    : m_type{ValType::Fn}, m_val{new Fn(f)} {}

// Static Method Constructors /////////////////////////////////////////////////

Value Value::True() { return Value(true); }

Value Value::False() { return Value(false); }

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

// Type Methods //////////////////////////////////////////////////////////////

// TODO these errors might also not be the best. It may be easier to do the
// checks in the core functions so that one can say things like
// "cannot apply: <value-rep>" without having to catch this error. Though it
// seems better to catch this error. The question might be whether we need to
// throw a proper lisp error or a C++ error just to indicate an error.
bool Value::get_bool() const {
  if (is_bool())
    return m_val.b;
  throw Error("Not a bool", *this);
}

int64_t Value::get_int() const {
  if (is_int())
    return m_val.i;
  throw Error("Not an int", *this);
}

double Value::get_flt() const {
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

// Checks /////////////////////////////////////////////////////////////////////

bool Value::is_truthy() const {
  return !(is_nil() or (is_bool() and !as_bool()));
}

// Overloads //////////////////////////////////////////////////////////////////

bool Value::operator==(const Value &other) const {
  switch (m_type) {
  case ValType::Bool:
    return other.is_bool() and as_bool() == other.as_bool();
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
