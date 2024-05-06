#ifndef LISCPP_TYPE_H
#define LISCPP_TYPE_H

#include <gc/gc_allocator.h>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace liscpp {

class Value;
class List;
class Generator;
class Fn;
class Stream;
class Error;
class GcMapValueCompare;

// Typedefs to use gc_allocator with built in types

typedef std::vector<Value, gc_allocator<Value>> GcVector;

typedef std::map<Value, Value, GcMapValueCompare,
                 gc_allocator<std::pair<const Value, Value>>>
    GcMap;

typedef std::basic_string<char, std::char_traits<char>, gc_allocator<char>>
    GcString;

typedef std::basic_ostringstream<char, std::char_traits<char>,
                                 gc_allocator<char>>
    GcOsStream;

typedef std::basic_istringstream<char, std::char_traits<char>,
                                 gc_allocator<char>>
    GcIsStream;

// GcMap needs a custom comparator to organize value types properly when they
// have the same and different types.

class GcMapValueCompare {
public:
  bool operator()(const Value &, const Value &) const;

private:
  bool compare_bool(bool, const Value &) const;
  bool compare_char(char, const Value &) const;
  bool compare_int(int64_t, const Value &) const;
  bool compare_float(double, const Value &) const;
  bool compare_keyword(GcString *, const Value &) const;
  bool compare_symbol(GcString *, const Value &) const;
  bool compare_string(GcString *, const Value &) const;
  bool compare_list(List *, const Value &) const;
  bool compare_vector(GcVector *, const Value &) const;
  bool compare_map(GcMap *, const Value &) const;
  bool compare_generator(Generator *, const Value &) const;
  bool compare_fn(Fn *, const Value &) const;
  bool compare_stream(Stream *, const Value &) const;
  bool compare_error(Error *, const Value &) const;
};

// Type enums for types using unions //////////////////////////////////////////

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
  Generator,
  // Function
  Fn,
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
  Closure,
};

enum class StreamType {
  Input,
  Output,
  InFile,
  OutFile,
};

enum class FileOp {
  Read,
  Write,
  Open,
  Close,
};

enum class ErrorType {
  Error,
  Arity,
  InvalidArg,
  OutOfBounds,
  Panic,
  File,
  IO,
};

// Type Functions and Ostream Overloads ///////////////////////////////////////

namespace __type__ {

GcString str(ValueType);
GcString str(FnType);
GcString str(StreamType);
GcString str(FileOp);
GcString str(ErrorType);

void code_rep(std::ostream &, const char &);
void code_rep(std::ostream &, const GcString &);
void code_rep(std::ostream &, const GcVector &);
void code_rep(std::ostream &, const GcMap &);

void display_rep(std::ostream &, const GcVector &);
void display_rep(std::ostream &, const GcMap &);

} // namespace __type__

} // namespace liscpp

std::ostream &operator<<(std::ostream &, const liscpp::GcString &);
std::ostream &operator<<(std::ostream &, const liscpp::GcVector &);
std::ostream &operator<<(std::ostream &, const liscpp::GcMap &);

std::ostream &operator<<(std::ostream &, const liscpp::ValueType &);
std::ostream &operator<<(std::ostream &, const liscpp::FnType &);
std::ostream &operator<<(std::ostream &, const liscpp::StreamType &);
std::ostream &operator<<(std::ostream &, const liscpp::FileOp &);
std::ostream &operator<<(std::ostream &, const liscpp::ErrorType &);

#endif
