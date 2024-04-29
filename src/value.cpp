#include "value.h"
#include "error.h"
#include "fn.h"
#include "generator.h"
#include "list.h"
#include "stream.h"
#include "type.h"
#include "value_functions.h"
#include <cstdint>

using namespace liscpp;

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
    return other.is_float() and as_flt() == other.as_flt();
  case ValueType::Symbol:
    return other.is_symbol() and as_symbol() == other.as_symbol();
  case ValueType::String:
    return other.is_string() and *as_str() == *other.as_str();
  case ValueType::List:
    return other.is_list() and *as_list() == *other.as_list();
  case ValueType::Vector:
    return other.is_vector() and *as_vector() == *other.as_vector();
  case ValueType::Map:
    return other.is_map() and *as_map() == *other.as_map();
  case ValueType::Generator:
    return other.is_generator() and as_generator() == other.as_generator();
  case ValueType::Fn:
    return other.is_fn() and as_fn() == other.as_fn();
  case ValueType::Stream:
    return other.is_stream() and as_stream() == other.as_stream();
  case ValueType::Error:
    return other.is_error() and as_error() == other.as_error();
  }
  return false;
}

// Representations ////////////////////////////////////////////////////////////

void Value::code_rep(std::ostream &os) const {
  switch (m_type) {
  case ValueType::Nil:
    os << "nil";
    break;
  case ValueType::Bool:
    os << (as_bool() ? "true" : "false");
    break;
  case ValueType::Char:
    os << "#\\" << as_char();
    break;
  case ValueType::Int:
    os << as_int();
    break;
  case ValueType::Float:
    os << as_flt();
    break;
  case ValueType::Symbol:
    os << as_symbol();
    break;
  case ValueType::Keyword:
    os << as_key();
    break;
  case ValueType::String:
    __type__::code_rep(os, *as_str());
    break;
  case ValueType::List:
    as_list()->code_rep(os);
    break;
  case ValueType::Vector:
    __type__::code_rep(os, *as_vector());
    break;
  case ValueType::Map:
    __type__::code_rep(os, *as_map());
    break;
  case ValueType::Generator:
    as_generator()->code_rep(os);
    break;
  case ValueType::Fn:
    as_fn()->code_rep(os);
    break;
  case ValueType::Stream:
    as_stream()->code_rep(os);
    break;
  case ValueType::Error:
    as_error()->code_rep(os);
    break;
  }
}

void Value::display_rep(std::ostream &os) const {
  return code_rep(os);
  switch (m_type) {
  case ValueType::Nil:
  case ValueType::Bool:
  case ValueType::Int:
  case ValueType::Float:
  case ValueType::Symbol:
  case ValueType::Keyword:
    code_rep(os);
    break;
  // Differ from code_rep or have their own rep functions
  case ValueType::Char:
    os << as_char();
    break;
  case ValueType::String:
    __type__::display_rep(os, *as_str());
    break;
  case ValueType::List:
    as_list()->display_rep(os);
    break;
  case ValueType::Vector:
    __type__::display_rep(os, *as_vector());
    break;
  case ValueType::Map:
    __type__::display_rep(os, *as_map());
    break;
  case ValueType::Generator:
    as_generator()->display_rep(os);
    break;
  case ValueType::Fn:
    as_fn()->display_rep(os);
    break;
  case ValueType::Stream:
    as_stream()->display_rep(os);
    break;
  case ValueType::Error:
    as_error()->display_rep(os);
    break;
  }
}
