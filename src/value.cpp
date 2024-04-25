#include "value.h"
#include "error.h"
#include "fn.h"
#include "stream.h"
#include "type.h"
#include <cstdint>
#include <format>
#include <iomanip>
#include <stdexcept>

// Static Method Constructors /////////////////////////////////////////////////

Value Value::new_true() {
  Value v;
  v.m_type = ValueType::Bool;
  v.m_val.b = true;
  return v;
}

Value Value::new_false() {
  Value v;
  v.m_type = ValueType::Bool;
  v.m_val.b = false;
  return v;
}

Value Value::new_char(char ch) {
  Value v;
  v.m_type = ValueType::Char;
  v.m_val.ch = ch;
  return v;
}

Value Value::new_int(int64_t i) { return Value{i}; }

Value Value::new_float(double d) { return Value{d}; }

// symbols and keywords might change internals, gonna keep it simple and just
// allow using string literals, but I think it will generally be better to
// explicitly construct the string with new and pass it into values.
Value Value::new_symbol(GcString*s) {
  Value v;
  v.m_type = ValueType::Symbol;
  v.m_val.str = s;
  return v;
}

Value Value::new_keyword(GcString*s) {
  Value v;
  v.m_type = ValueType::Keyword;
  v.m_val.str = s;
  return v;
}

Value Value::new_string(GcString *s) {
  Value v;
  v.m_type = ValueType::String;
  v.m_val.str = s;
  return v;
}

// Value Value::List(List*);
Value Value::new_vector(GcVector *vec) {
  Value v;
  v.m_type = ValueType::Vector;
  v.m_val.vec = vec;
  return v;
}

// Value Value::Map(std::map<Value, Value>*);
// Value Value::Iterator();

Value Value::new_fn(Fn *f) {
  Value v;
  v.m_type = ValueType::Fn;
  v.m_val.fn = f;
  return v;
}

Value Value::new_closure(Closure *c) {
  Value v;
  v.m_type = ValueType::Closure;
  v.m_val.closure = c;
  return v;
}

Value Value::new_stream(Stream *s) {
  Value v;
  v.m_type = ValueType::Stream;
  v.m_val.stream = s;
  return v;
}

Value Value::new_error(Error *e) {
  Value v;
  v.m_type = ValueType::Error;
  v.m_val.err = e;
  return v;
}

// Overloads //////////////////////////////////////////////////////////////////

// NOTE these need to be deep equality, not just pointer comparissons
bool Value::operator==(const Value &other) const {
  switch (m_type) {
  case ValueType::Nil:
    return other.is_nil();
  case ValueType::Bool:
    return other.is_bool() and as_bool() == other.as_bool();
  case ValueType::Char:
    return other.is_char() and as_char() == other.as_char();
  case ValueType::Int:
    return other.is_int() and as_int() == other.as_int();
  case ValueType::Float:
    return other.is_float() and as_flt() == other.as_flt();
  case ValueType::Keyword:
    return other.is_keyword() and as_key() == other.as_key();
  case ValueType::String:
    return other.is_string() and *as_str() == *other.as_str();
  case ValueType::Vector:
    return other.is_vector() and *as_vector() == *other.as_vector();
  case ValueType::Fn:
    return other.is_fn() and *as_fn() == *other.as_fn();
  case ValueType::Stream:
    return other.is_stream() and as_stream() == other.as_stream();
  case ValueType::Error:
    return other.is_error() and *as_error() == *other.as_error();
  }
  throw type::throw_uncovered_type("Value::operator==", int(m_type));
}

// Representations ////////////////////////////////////////////////////////////

void Value::to_external(std::ostream &os) const {
  switch (m_type) {
  case ValueType::Nil:
    os << "nil";
    break;
  case ValueType::Bool:
    os << (as_bool() ? "true" : "false");
    break;
  case ValueType::Char:
    os << as_char();
    break;
  case ValueType::Int:
    os << as_int();
    break;
  case ValueType::Float:
    os << as_flt();
    break;
  case ValueType::Keyword:
    os << as_key();
    break;
  case ValueType::String:
    os << '"' << *as_str() << '"';
    break;
  case ValueType::Vector: {
    GcVector *v = as_vector();
    os << "[";
    if (v->size() > 0) {
      for (auto it = v->begin(); it != v->end() - 1; ++it) {
        os << *it << ", ";
      }
      os << v->back();
    }
    os << "]";
    break;
  }
  case ValueType::Fn: {
    // TODO should we add mod names to Fn as well ???
    Fn *f = as_fn();
    os << "#<Fn: " << f->get_name() << "(" << f->get_arity() << ")"
       << ">";
    break;
  }
  case ValueType::Closure:
    // TODO fix if closure has more data that can be used
    os << "#<Closure>";
    break;
  case ValueType::Stream: {
    Stream *s = as_stream();
    os << "#<Stream: " << s->get_type() << ">";
    break;
  }
  case ValueType::Error:
    // TODO overlaod error types with these output methods and give a nice
    // representation of the error object.
    os << "#<Error>";
    break;
  default:
    throw type::throw_uncovered_type("Value::to_external", int(m_type));
  }
}

void Value::to_display(std::ostream &os) const {
  // FIXME where display does not match external
  return to_external(os);
}

std::ostream &operator<<(std::ostream &os, const Value &value) {
  value.to_external(os);
  return os;
}
