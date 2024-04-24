#include "type.h"
#include <exception>
#include <format>
#include <stdexcept>
#include <string>

std::invalid_argument type::throw_uncovered_type(const std::string &where,
                                                 int type_as_int) {
  return std::invalid_argument(std::format(
      "in {} found uncovered enum type: Type as int = {}", where, type_as_int));
}

std::string type::str(ValueType t) {
  switch (t) {
  case ValueType::Nil:
    return "ValueType::Nil";
  case ValueType::Bool:
    return "ValueType::Bool";
  case ValueType::Char:
    return "ValueType::Char";
  case ValueType::Int:
    return "ValueType::Int";
  case ValueType::Float:
    return "ValueType::Float";
  case ValueType::Symbol:
    return "ValueType::Symbol";
  case ValueType::Keyword:
    return "ValueType::Keyword";
  case ValueType::String:
    return "ValueType::String";
  case ValueType::List:
    return "ValueType::List";
  case ValueType::Vector:
    return "ValueType::Vector";
  case ValueType::Map:
    return "ValueType::Map";
  case ValueType::Iterator:
    return "ValueType::Iterator";
  case ValueType::Fn:
    return "ValueType::Fn";
  case ValueType::Closure:
    return "ValueType::Closure";
  case ValueType::Stream:
    return "ValueType::Stream";
  case ValueType::Error:
    return "ValueType::Error";
  default:
    throw std::invalid_argument(std::format("uncovered ValueType: {}", int(t)));
  }
}

std::string type::str(FnType t) {
  switch (t) {
  case FnType::Fn0:
    return "FnType::Fn0";
  case FnType::Fn1:
    return "FnType::Fn1";
  case FnType::Fn2:
    return "FnType::Fn2";
  case FnType::Fn3:
    return "FnType::Fn3";
  case FnType::Fn4:
    return "FnType::Fn4";
  case FnType::Fn5:
    return "FnType::Fn5";
  case FnType::FnAny:
    return "FnType::FnAny";
  default:
    throw std::invalid_argument(std::format("uncovered ValueType: {}", int(t)));
  }
}

std::string type::str(StreamType t) {
  switch (t) {
  case StreamType::Input:
    return "StreamType::Input";
  case StreamType::Output:
    return "StreamType::Output";
  case StreamType::InFile:
    return "StreamType::InFile";
  case StreamType::OutFile:
    return "StreamType::OutFile";
  default:
    throw std::invalid_argument(std::format("uncovered ValueType: {}", int(t)));
  }
}

std::ostream &operator<<(std::ostream &os, const ValueType &type) {
  os << type::str(type);
  return os;
}

std::ostream &operator<<(std::ostream &os, const FnType &type) {
  os << type::str(type);
  return os;
}

std::ostream &operator<<(std::ostream &os, const StreamType &type) {
  os << type::str(type);
  return os;
}
