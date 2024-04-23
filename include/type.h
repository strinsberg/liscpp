#ifndef LISCPP_TYPE_H
#define LISCPP_TYPE_H

#include <string>

enum class ValueType {
  // Primitive
  Nil,
  Bool,
  Char,
  Int,
  Float,
  // String
  Symbol,
  Keyword,
  String,
  // Collections
  List,
  Vector,
  Map,
  Iterator,
  // Function
  Fn,
  Closure,
  // Other
  Stream,
  Error,
};

enum class FnType {
  Fn0,
  Fn1,
  Fn2,
  Fn3,
  Fn4,
  Fn5,
  FnAny,
};

enum class StreamType {
  Input,
  Output,
  InFile,
  OutFile,
};

namespace type {
std::string str(ValueType);
std::string str(FnType);
std::string str(StreamType);
} // namespace type

std::ostream &operator<<(std::ostream &, const ValueType &);
std::ostream &operator<<(std::ostream &, const FnType &);
std::ostream &operator<<(std::ostream &, const StreamType &);

#endif
