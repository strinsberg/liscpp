#include "value.h"
#include "error.h"
#include "fn.h"
#include <cstdint>
#include <format>
#include <stdexcept>

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

// TODO where are these used? in compiled code? There errors should be panics
// that cannot be recovered from as if bad access occurs it is a compiler or
// lib error. All hand coded uses of values will manually check types and
// access to reduce double checking for types. Though it may be best to add
// the panic and always use these for safety.

bool Value::get_bool() const {
  if (is_bool())
    return m_val.b;
  throw Panic(std::format("attempt to access Value as Bool: Actual type is {}",
                          type_string()));
}

int64_t Value::get_int() const {
  if (is_int())
    return m_val.i;
  throw Panic(std::format(
      "attempt to access Value as Integer: Actual type is {}", type_string()));
}

double Value::get_flt() const {
  if (is_flt())
    return m_val.d;
  throw Panic(std::format("attempt to access Value as Float: Actual type is {}",
                          type_string()));
}

const std::string &Value::get_key() const {
  if (is_key())
    return *m_val.s;
  throw Panic(std::format(
      "attempt to access Value as Keyword: Actual type is {}", type_string()));
}

std::string *Value::get_str() const {
  if (is_str())
    return m_val.s;
  throw Panic(std::format(
      "attempt to access Value as String: Actual type is {}", type_string()));
}

Fn *Value::get_fn() const {
  if (is_fn())
    return m_val.f;
  throw Panic(std::format(
      "attempt to access Value as Function: Actual type is {}", type_string()));
}

Error *Value::get_error() const {
  if (is_err())
    return m_val.e;
  throw Panic(std::format("attempt to access Value as Error: Actual type is {}",
                          type_string()));
}

// Util ///////////////////////////////////////////////////////////////////////

bool Value::is_truthy() const {
  return !(is_nil() or (is_bool() and !as_bool()));
}

const std::string Value::type_string() const {
  switch (m_type) {
  case ValType::Nil:
    return "Nil";
  case ValType::Bool:
    return "Bool";
  case ValType::Int:
    return "Integer";
  case ValType::Flt:
    return "Float";
  case ValType::Key:
    return "Keyword";
  case ValType::Str:
    return "String";
  case ValType::Fn:
    return "Function";
  case ValType::Err:
    return "Error";
  }
  throw Panic(std::format("value::type_string encountered uncovered type {}",
                          int(m_type)));
}

// Overloads //////////////////////////////////////////////////////////////////

// NOTE these need to be deep equality, not just pointer comparissons
bool Value::operator==(const Value &other) const {
  switch (m_type) {
  case ValType::Nil:
    return other.is_nil();
  case ValType::Bool:
    return other.is_bool() and as_bool() == other.as_bool();
  case ValType::Int:
    return other.is_int() and as_int() == other.as_int();
  case ValType::Flt:
    return other.is_flt() and as_flt() == other.as_flt();
  case ValType::Key:
    return other.is_key() and as_key() == other.as_key();
  case ValType::Str:
    return other.is_str() and *as_str() == *other.as_str();
  case ValType::Fn:
    return other.is_fn() and *as_fn() == *other.as_fn();
  case ValType::Err:
    // TODO this is shallow eq for errors
    return other.is_err() and as_error() == other.as_error();
  }
  throw Panic(std::format("value::operator== encountered uncovered type {}",
                          int(m_type)));
}
